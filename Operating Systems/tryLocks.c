#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//fix the sync problem by using a POSIX lock
//current output:
//Task 1 has started
//Task 2 has started
//Task 2 has finished
//Task 2 has finished

pthread_t tid[2];
int counter;
pthread_mutex_t lock; //create mutex lock

void* tryLocks(void* arg)
{
	pthread_mutex_lock(&lock); //lock the door until current task finished

	unsigned long i = 0;
	counter += 1;
	printf("\n Task %d has started\n", counter);
	for (i = 0; i < (0xFFFFFFFF); i++)
	;
	printf("\n Task %d has finished\n", counter);

	pthread_mutex_unlock(&lock); // unlock so next task can begin

	return NULL;
}
int main(void)
{
	int i = 0;
	int error;
	//check to see if lock was succesfully created
	if(pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex failed \n");
		return 1;
	}

	while ( i < 2) {
		error = pthread_create(&(tid[i]), NULL, &tryLocks, NULL);
		if (error != 0)
			printf("\n Thread not created : [%s]", strerror(error));
		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
