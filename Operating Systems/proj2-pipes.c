#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50

int main(int argc, char* argv[]){
	//error check and etc
	if(argc != 2){
		printf("Pass me an integer please\n");
		return -1;
	}	
	pid_t pid;
	int fd[2];
	const char *input = argv[1];
	char *write_msg = (char*)malloc(MAXSIZE * sizeof(char));
	char read_msg[MAXSIZE];

	//check command line input
	if(!isdigit(input[0])){
		printf("Invalid input: %s\n", input);
		return -1;
	}
	//input to pass to child
	int a = strtoimax(input, (char **)NULL, 10);
	if (a <= 0){
		printf("Invalid number: %d\n", a);
		return -1;
	}
	sprintf(write_msg, "%d\n", a);
	int *b = &a;
	//create the pipe
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe failed");
		return -1;
	}

	//now fork a child process
	pid = fork();

	if(pid < 0){
		printf("Fork failed");
		return 1;
	}
	
	else if(pid == 0){//child does math and writes
		while(*b != 1){
			//write to pipe
			write(fd[1], write_msg, strlen(write_msg));
			//do math
			if(*b % 2 == 0){
				*b = *b / 2;
			}
			else
				*b = (3 * *b) +1;
			//pass num into write message
			sprintf(write_msg, "%d\n", *b);
		}
		write(fd[1], write_msg, strlen(write_msg));
	}
	else{
		wait(NULL);
		read(fd[0], read_msg, MAXSIZE);
		printf("%s\n", read_msg);
		//close read and write
		close(fd[0]);
		close(fd[1]);
	}
	free(write_msg);
	return 0;
}
