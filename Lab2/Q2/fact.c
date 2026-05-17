#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<sys/time.h>
#include<sys/wait.h>

int main(int argc, char **argv){
   /*Your code goes here */
    if(argc==2){
		long num=atoi(argv[1]);
		if(num==1){
			printf("1\n");
			return 0;
		}
		char ex[26];
		sprintf(ex,"%ld",num-1);
		char* e[] = {argv[0],ex,argv[1],NULL};
		execve(argv[0],e,NULL);
	}
	else{
		long num = atol(argv[1]);
		if(num==2){
			long ans = 2*atol(argv[2]);
			printf("%ld\n",ans);
			return 0;
		}
		long n =num*atol(argv[2]);
		char d1[26],d2[26];
		sprintf(d1,"%ld",num-1);
		sprintf(d2,"%ld",n);
		char *e[] = {argv[0],d1,d2,NULL};
		execve(argv[0],e,NULL);
	}
   return 0;
}
