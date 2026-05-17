#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<sys/time.h>
#include<sys/wait.h>


extern int isPrime(long x); // Returns zero if composite.
                            // Returns one if prime. You may use this if you want. 
int find_primes(long M)
{
  //Your code goes in here
   long cnt1=0;
   long cnt2=0;   
   
   pid_t pid;
   pid=fork();
   if(!pid){
    for(long i=2;i<=M/2;i++){
    	if(isPrime(i)==1){
	cnt1++;
	}
      }
    long ans=cnt1%256;
    exit(ans);    
   }
   else{
    pid_t pid2;
    pid2 = fork();
    if(!pid2){
     for(long i=M/2+1;i<=M;i++){
        if(isPrime(i)==1){
        cnt2++;
        }
      }
    long  ans=cnt2%256;
     exit(ans);
     }
   }
   wait(&cnt1);
   wait(&cnt2);

   return (WEXITSTATUS(cnt1)+WEXITSTATUS(cnt2))%256;   
}
