//Nathaniel Taylor
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
	//error checking and etc
	if( argc != 2 ){
		printf("Pass me an integer please");
		return 0;
	}
	pid_t pid;
	const char *input = argv[1];

	const char *name = "OS1";
	const int SIZE = 4096;

	//check command line arguements
	if(!isdigit(input[0])){
		printf("inavalid input: %s", input);
		return -1;
	}	
	int a = strtoimax(input, (char **)NULL, 10);
	if (a <= 0 ) {
		printf("Number is too low: %d", a);
		return -1;
	}
	
	//create child
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	//if parent
	else if (pid > 0 ) {
		wait(NULL);
		int shm_fd;
		void *ptr;
		int i;
		
		//open shared mem segment
		shm_fd = shm_open(name, O_RDONLY, 0666);		
		if (shm_fd == -1) {
			printf("Shared mem failed in parent\n");
			exit(-1);
		}
		//map shared memory segment in address space of the process
		ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		if( ptr == MAP_FAILED) {
			printf("Map failed\n");
			exit(-1);
		}
	
		//read from shared mem region
		printf("%s\n",(char *)ptr);
	
		//remove shared mem region
		if(shm_unlink(name) == -1) {
			printf("Error removing %s\n", name);
			exit(-1);
		}
	}
	//else its child
	else {
		int shm_fd;
		void *ptr;
		//create shared mem segment
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		
		//configure size of shared mem segment
		ftruncate(shm_fd, SIZE);
		//map shared mem segment in address space
		ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if (ptr == MAP_FAILED){
			printf("Map failed in child\n");
			return -1;
		}
		int *b = &a;

	//do math and pass sequence back to parent
		while(*b != 1){
			//write to shared mem			
			sprintf(ptr, "%d", *b);
			ptr += (int)floor(log10(abs(*b))) + 1;
			sprintf(ptr, "\n");
			ptr += 1;
			
			
			//do math
			if(*b % 2 == 0){
				*b = *b / 2;
			}
			else { 
				*b = (3 * *b) + 1;
			}
		}
		sprintf(ptr, "%d", *b);
		ptr += 1;		
	}
	return 0;
}
