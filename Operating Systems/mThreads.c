//This program will create a number of threads specified on the command line
//Each thread will print out a greeting and its own thread identifier.
//To be sure to see how the threads behave,
//make the main thread sleep for every 4 threads it creates

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define MAX_THREADS 50

pthread_t thread_id[MAX_THREADS];

void * PrintHello(void * data) 
{
	printf("Hello from thread %u = I was created in iteration %ld !\n", (int)pthread_self(), (intptr_t)data);
	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
	int rc, i, n;

	if(argc < 2)
	{
		printf("Please add the number of threads to the command line\n");
		exit(1);
	}
	n = atoi(argv[1]);
	if(n > MAX_THREADS) n = MAX_THREADS;
	int *temp = NULL;
	for(i = 0; i < n; i++)
	{
		temp = &i;
		if(pthread_create(&thread_id[i], NULL, PrintHello, (void *)*temp) != 0){
			printf("Error pthread_create failed");
			return 1;
		}
		if(i % 5 == 0) sleep(1);
		
	}
	for(int j = 0; j < n; j++)
		pthread_join(thread_id[j], NULL);
	return 0;
}
