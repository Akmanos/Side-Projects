#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define MIN_PID 100
#define MAX_PID 300
#define SLEEP 5 /* sleep((int)(random()%SLEEP)); */ //this will call random then sleep under 5 secs

int allocate_pid(void);
/*this function creates a data structure for representing the PIDs and if the number is
* taken or not. 
* it returns 1 if successful and -1 if not successful
*/
int pids[MAX_PID - MIN_PID] = {0};
pthread_mutex_t lock;

int allocate_ds(void){
	int error = -1;
	int i = allocate_pid();
	if(i != -1)
		pids[i] = 1;
	return error;
}

/* this function allocates and returns a PID to the calling thread. Returns -1 if unable 
* to allocate a PID */
int allocate_pid(void){
	for(int i = 0; i < MAX_PID - MIN_PID; i++){
		//if it's available
		if(pids[i] == 0){
			return i;
		}
	}
	return -1;
}

/* This function is called right before the thread terminates to release the PID */
void release_pid(int pid){
	pids[pid] = 0;
}
//method call for multithreaded program
void* meThreads(void* arg){
	int thread_id = *((int *) arg);
	//get an available pid
	int id = allocate_pid();
	//set it to taken
	allocate_ds();
	//if there are no pids available pids
	if(id == -1){
		printf("No available ids");
		return NULL;
	}
	pthread_mutex_lock(&lock);//mutex lock after allocating a pid

	printf("Current thread: %3d and pid: %d created\n", thread_id, id+MIN_PID);
	//sleep
	sleep((int)(random() % SLEEP));
	//release the pid
	release_pid(id);
	printf("Thread: %3d ended. pid: %d released\n", thread_id, id+MIN_PID);

	pthread_mutex_unlock(&lock);//unlock
	pthread_exit(NULL);
}

int main(void){
	int error;
	pthread_t tid[NUM_THREADS];
	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("mutex init failed\n");
		return 1;
	}
	//create 100 threads
	for(int i = 0; i < MIN_PID; i++){
		error = pthread_create(&(tid[i]), NULL, &meThreads, (void*)&i);
		if (error != 0)
			printf("Error creating thread");
	}
	for(int j = 0; j < MIN_PID; j++)
		pthread_join(tid[j], NULL);
}
