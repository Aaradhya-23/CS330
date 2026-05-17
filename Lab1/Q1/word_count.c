#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>

// Use Library function such as fopen, geline, fread etc
// use manpages as mentioned in the writeup. 
// -----------------------
//
//
// Your solution begins here




int main(int argc, char *argv[]){
        FILE *stream;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;

        if (argc !=3) {
            return -1;
        }

        stream = fopen(argv[2], "r");
        if (stream == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        ssize_t c_cnt =0;
	    ssize_t w_cnt =0;
	    ssize_t l_cnt = 0;

        while ((nread = getline(&line, &len, stream)) != -1){
            c_cnt += nread;
            l_cnt++;
            int flag = 0;
            for(ssize_t i =0;i<nread; i++){

                if(isspace((unsigned char)line[i])){
                    flag = 0;

                }	
                else if(!flag){
                    w_cnt++;
                    flag = 1;
                }
           }
	    }

        free(line);
        fclose(stream);

        if(strcmp(argv[1], "-c")==0){
            printf("%zu",c_cnt);
        }
        else if(strcmp(argv[1], "-w")==0){
            printf("%zu",w_cnt);
        }
        else if(strcmp(argv[1], "-l")==0){
            printf("%zu",l_cnt);
        }
        else{
            return -1;
        }
        exit(EXIT_SUCCESS);
}



