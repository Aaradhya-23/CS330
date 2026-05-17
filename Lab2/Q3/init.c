#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int is_alnum_char(char c){
	return ((c>='0' && c<= '9') || (c>='a' && c<= 'z')|| (c>='A' && c <= 'Z'));
}

int main(int argc, char **argv){
	if(argc !=3){
		printf("Error\n");
		return 0;
	}
	char  *term = argv[1];
	char *fname = argv[2];

	if(term[0] == '\0'){
		printf("Error\n");
		return 0;
	}

	for(size_t i =0; i<strlen(term);i++){
		if(!is_alnum_char(term[i])){
			printf("Error\n");
			return 0;
		}
	}
	int fd = open(fname,O_RDONLY);
	if(fd<0){
	    printf("Error\n");
		return 0;
	}
	const size_t BUF_SZ = 4096;
	char buf[4096];
	ssize_t r;
	char* word = malloc(256);
	if(!word) { 
		close(fd);
		printf("Error\n");
        return 0;
	}
    size_t wlen = 0;
	int found =0;
	while((r=read(fd,buf,BUF_SZ)) >0 && !found){
		for(ssize_t i=0;i<r && !found;i++){
			char c = buf[i];
			if(is_alnum_char(c)){
				if(wlen + 1>= 256){
					wlen = 0;
				}
				word[wlen++] = c;
			}
			else{		
				if(wlen >0){
					word[wlen] = '\0';
					if(strstr(word,term) != NULL){
						found = 1;
						break;
					}
					wlen =0;
				}
			}
		}
	}
	if(!found && wlen >0){
		word[wlen] = '\0';
		if(strstr(word,term) !=NULL) found =1;
	}
	if( r <0){
		close(fd);
		printf("Error\n");
		return 0;
	}
	free(word);
	close(fd);
	if(found) printf("FOUND\n");
	else printf("NOT FOUND\n");
	return 0;
}

