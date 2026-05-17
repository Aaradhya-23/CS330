#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include <fcntl.h>
int comp( char*str1, char *str2, int n){
	for(int i=0;i < n;i++){
		if(str1[i+7]!=str2[i] || str1[i] == '\0') return  str1[i] - str2[i];

	}
	return 0;
}
int main(int argc, char **argv){
	if(argc!=2){
	       printf("Unable to execute");
		exit(-1);
	}
	int fd=open(argv[1],O_RDONLY);
	if(fd==-1){
		printf("Unable to execute");
		exit(-1);
	}
	char buff[4096];
	char line[256];
	int line_pos=0;
	ssize_t bytes;
	int openat_c =0, close_c =0, read_c =0,write_c = 0,stat_c =0,execve_c =0;
         
	while((bytes= read(fd,buff,sizeof(buff))) > 0){
		for(int i=0;i<bytes;i++){
			if(buff[i] == '\n'){
				line[line_pos] = '\0';

				if(comp(line,"openat(",7)==0) openat_c++;
				if(comp(line,"close(",6)==0) close_c++;
                if(comp(line,"read(",5)==0) read_c++;
                if(comp(line,"write(",6)==0) write_c++;
                if(comp(line,"stat(",5)==0) stat_c++;
       			if(comp(line,"execve(",7)==0) execve_c++;
                line_pos =0;
			}
			else{
				if(line_pos < sizeof(line)-1)
				line[line_pos++] = buff[i];
			}
		}
	}

	if(bytes == -1){
		printf("Unable to execute\n");
		close(fd);
		exit(-1);
	}
	close(fd);
    printf("openat: %d\n",openat_c);
    printf("close: %d\n",close_c);
    printf("read: %d\n",read_c);
    printf("write: %d\n",write_c);
    printf("stat: %d\n",stat_c);
    printf("execve: %d\n",execve_c);

    return 0;
}
