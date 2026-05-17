#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<string.h>
#include <sys/syscall.h>
extern int isPrime(long x); // Returns zero if composite.
                            // Returns one if prime. 

long find_primes(int num_cp, long M)
{
   /*
    *  TODO 
    *  Your code goes here
    */
    long total_primes =0;	
    int pipes[num_cp][2];
for(int i=0;i<num_cp;i++){
	 if(syscall(SYS_pipe,pipes[i]) ==-1){
	 printf("pipe\n");
	 exit(EXIT_FAILURE);
	 }
}	

    for(int i=0;i<num_cp;i++){
		pid_t pid=fork();
		if(pid<0){
			printf("fork\n");
		exit(EXIT_FAILURE);
		}
		if(pid==0){ //child
			close(pipes[i][0]);
			for(int j=0;j<num_cp;j++){
				if(i!=j){
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
			}
			long start=((long)i*M/num_cp)+1;
			long  end=(long)(i+1)*M/num_cp;
			if(i==num_cp-1){ //for the last case, i+1 <= num_cp
				end=M;
			}
			long partial_count=0;
			for(long  k=start;k<=end;k++){
				if(isPrime(k)){
					partial_count++;	
				}
			}
			if(write(pipes[i][1],&partial_count,sizeof(partial_count))==-1){
				printf("write\n");
				exit(EXIT_FAILURE);
			}
			close(pipes[i][1]);
			exit(EXIT_SUCCESS);
		}
	}

	for(int i=0;i<num_cp;i++){ //close write end for parent
		close(pipes[i][1]);
	}

	for(int i=0;i<num_cp;i++){
		long partial_count=0;
		if(read(pipes[i][0],&partial_count,sizeof(partial_count))==-1){
			printf("read\n");
			exit(EXIT_FAILURE);
		}
		total_primes+=partial_count;
		close(pipes[i][0]);
	}
	for(int i=0;i<num_cp;i++){
		wait(NULL);
	}


   return total_primes;   
}
