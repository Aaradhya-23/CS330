#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHARS_IN_LINE 1000
ssize_t read_line(int fd, char* buffer){
    ssize_t len = 0;
	while(len < MAX_CHARS_IN_LINE-1){
		ssize_t bytes_read = read(fd,buffer+len,1);
		if(bytes_read <= 0){break;}
		len++;
		if(buffer[len-1]=='\n'){
			break;
		}
	}
	buffer[len] = '\0';
	return len;
}

int main(int argc, char **argv)
{
	char buf[MAX_CHARS_IN_LINE+1];
	char obuf[MAX_CHARS_IN_LINE+1];

// NOTE: Do not modify anything above this line	
/***
 *      Your Code goes here
 */	
	if(argc != 3){
		write(STDOUT_FILENO,"Error\n",6);
		exit(1);
	}
	int output_fd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
	
	if(output_fd < 0){
	//close(output_fd);
		write(STDOUT_FILENO,"Error\n",6);
		exit(1);
	}
	int input_fd = open(argv[1],O_RDONLY);
	int parent_to_child[2];
	int child_to_parent[2];

	if(syscall(SYS_pipe,parent_to_child)==-1 ||syscall(SYS_pipe, child_to_parent)==-1){
		write(STDOUT_FILENO,"Error\n",6);
		exit(1);
	}
	pid_t pid= fork();
	if(pid <0){
		write(STDOUT_FILENO,"Error\n",6);
		exit(1);
	}
	if(pid == 0){
		close(parent_to_child[1]);
		close(child_to_parent[0]);
		if(dup2(parent_to_child[0],STDIN_FILENO)==-1){
			write(STDOUT_FILENO,"Error\n",6);
			exit(1);
		}
		if(dup2(child_to_parent[1],STDOUT_FILENO)==-1){
            write(STDOUT_FILENO,"Error\n",6);
			exit(1);
        }
		close(parent_to_child[0]);
        close(child_to_parent[1]);
		execl("./encrypt","encrypt",NULL);
		write(STDOUT_FILENO,"Error\n",6);
		exit(1);
	}
	else{
		close(parent_to_child[0]);
        close(child_to_parent[1]);
        char line_buffer[MAX_CHARS_IN_LINE];
		char len_buffer[16];
		ssize_t bytes_read;
		while((bytes_read = read_line(input_fd,line_buffer)) > 0){
			int len = sprintf(len_buffer,"%ld\n", bytes_read);
			write(parent_to_child[1],len_buffer,len);
			write(parent_to_child[1],line_buffer,bytes_read);
		}
		close(parent_to_child[1]);
		while((bytes_read = read(child_to_parent[0],line_buffer,MAX_CHARS_IN_LINE))>0){
			write(output_fd,line_buffer,bytes_read);
		}
		close(child_to_parent[0]);
		close(output_fd);
		close(input_fd);
		wait(NULL);
	} 

 return 0;
}

