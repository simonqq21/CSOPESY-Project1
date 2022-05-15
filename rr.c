#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "rr.h"

/*	This function copies the processes' PID and original burst time to keep track of the 
	original burst time, which is needed for computing waiting time
	@param processes[] is an array of struct that will store pid and original burst times of processes
	@param *processList points to the linked list of processes
	@param numProcesses total number of processes, to ensure it does not exceed allocated memory for the array
*/
void initProcessIDBurst(ProcessIDBurst processes[], Process_t *processList, int numProcesses) {
	Process_t *tmp = processList;
	int i = 0;

	while(tmp != NULL && i < numProcesses) {
		processes[i].pid = tmp->pid;
		processes[i].origBurst = tmp->burst;
		tmp = tmp->next;
		i++;
	}
}

/*	This function is used to queue a process to a ready Queue
	@param *process pointer to the processes 
	@param *queue pointer to the head of the list of executed processes
*/
void enqueue(Process_t *process, Queues *queue) {
	Process_t *newProcess = malloc(sizeof(Process_t));

	if (newProcess == NULL) {
		printf("Memory not allocated.\n");
	} else {
		//Initializing new process to be added to the readyQueue
		newProcess->pid = process->pid;
        newProcess->arrival = process->arrival;
        newProcess->burst = process->burst;
        newProcess->next = NULL;
		if(process->timeframes == NULL) {
			newProcess->timeframes = NULL;
		} else {
			newProcess->timeframes = process->timeframes;
		}
		//Adding to queue - if tail exists, connect current tail to new node
		if(queue->tail != NULL) {
			queue->tail->next = newProcess;
		}
		queue->tail = newProcess; //new tail is the new node

		// If currently no head
		if (queue->head == NULL) {
			queue->head = newProcess;
		}
	}
}

/*	This process dequeues a node in the queue
	@param *queue is a variable that points to the address of the queue
*/
Process_t *dequeue(Queues *queue) {
 	Process_t *tmpFree;
	if(queue->head == NULL) {
		return NULL;
	} else {
		Process_t *dequeuedNode = (Process_t *) malloc(sizeof(Process_t));
		tmpFree = queue->head;
		*dequeuedNode = *tmpFree; //copy content
		queue->head = queue->head->next;
		if(queue->head == NULL) {
			queue->tail = NULL;
		}
		free(tmpFree);
		return dequeuedNode;
	}
	
}


/*	This function enqueues the arrived processes to the ready queue of the function
	@param *currTime pointer to the current execution time
	@param *queue points to the address of the queue
*/
void enqueueArrivedProcesses(int *currTime, Process_t ** processList, Queues *queue, int *numProcesses) {
	Process_t *tmp = *processList; 

	if(*numProcesses != 0) {
		while (tmp != NULL) {
			if(tmp->arrival <= *currTime) {
				enqueue(tmp, queue);
				*numProcesses = deleteProcess(tmp->pid, processList, *numProcesses); //delete process to avoid duplication
			}
			tmp = tmp->next;
		}
	} 
}

/*	This function executes the dequeued process from the ready queue, returns the pointer to the dequeued and executed node
	This function should not be executed when 

*/
Process_t *executeReadyQueue(Queues *readyQueue, int *currTime, int timeSlice, int *numProcess) {
	Process_t *dequeuedNode;
	int executedTime = 0;
	int start = 0;
	Timeframe_t *tempTime;
	int burstLeft = 0;
	
	dequeuedNode = dequeue(readyQueue); //dequeue arrived process from readyQueue to execute, separate address
	if(dequeuedNode != NULL) {
		burstLeft = dequeuedNode->burst;
		start = *currTime;
		//Calculate remaining burst time
		if(burstLeft < timeSlice) {
			executedTime = start + burstLeft;
			dequeuedNode->burst = burstLeft - burstLeft;
		}
		else if (burstLeft >= timeSlice) {
			executedTime = start + timeSlice;
			dequeuedNode->burst = burstLeft - timeSlice;
		}
		*currTime = executedTime;

		//Adjust timeframe; if no time frames have been initialized
		if (dequeuedNode->timeframes == NULL) {
			dequeuedNode->timeframes = createTimeframe(start, executedTime);
		} else {
			tempTime = dequeuedNode->timeframes; //head of the timeframes
			while (tempTime->next != NULL) {
				tempTime = tempTime->next;
				//loop until the next node of the time list is NULL
			} 
			tempTime->next = createTimeframe(start, executedTime);
			//dequeuedNode->timeframes = tempTime;
		}
	}
	return dequeuedNode;
}

/*	This function checks if the queue is empty or not
	@param *queue is a pointer to the queue
*/
int queueIsEmpty(Queues *queue) {
	int result = 1;
	if(queue->head != NULL && queue->tail != NULL)
		result = 0;
	return result;
}

/*	This function checks if the list of processes is empty or not
	@param *queue is a pointer to the processList
*/
int listIsEmpty(Process_t *processList) {
	int result = 1;
	if(processList != NULL)
		result = 0;
	return result;
}

/* This function prints the executed processes
	@param *queue pointer to the queue
*/
void printRoundRobinResult(Queues *queue) {
	Process_t *dequeuedNode;
	Timeframe_t *tempTime;
	float aveWaiting = 0;
    aveWaiting = getAverageWaitingTime(queue->head);
	dequeuedNode = dequeue(queue);
	while(dequeuedNode != NULL){
		printf("P[%d] ", dequeuedNode->pid);
		tempTime = dequeuedNode->timeframes;
		printf("Start Time: %d End time: %d", tempTime->start, tempTime->end);
		tempTime = tempTime->next;
		while(tempTime != NULL) {
			printf(" | Start Time: %d End time: %d", tempTime->start, tempTime->end);
			tempTime = tempTime->next;
		}
		printf(" | Waiting time: %d\n", getProcessWaitingTime(dequeuedNode));
		dequeuedNode = dequeue(queue);
	}
	printf("Average waiting time: %.1f\n", aveWaiting);
}

/*	This function executes the processes using the round robin algorithm
	@param *processList pointer to the list of processes
	@param numProcesses total number of processes
	@param timeSlice time quantum needed for executing algorithm
*/
void rr(Process_t * processList, int numProcesses, int timeSlice) {
	int currTime = 0;
	Process_t *dequeuedNode;
	Queues readyQueue;
	Queues finishedQueue;
	int finish = 0;

	//Array of structs to store original burst time for calculation later on
	ProcessIDBurst *processIdAndBurst = malloc(numProcesses * sizeof(ProcessIDBurst)); 

	initQueue(&readyQueue);
	initQueue(&finishedQueue);
	initProcessIDBurst(processIdAndBurst, processList, numProcesses);

	while(!finish) {
		enqueueArrivedProcesses(&currTime, &processList, &readyQueue, &numProcesses);
		dequeuedNode = executeReadyQueue(&readyQueue, &currTime, timeSlice, &numProcesses);
		if(dequeuedNode != NULL) {
			enqueueArrivedProcesses(&currTime, &processList, &readyQueue, &numProcesses); //enqueue all arrived processes first
			if(dequeuedNode->burst != 0)
				enqueue(dequeuedNode, &readyQueue);	 // put it back to the ready queue when burst > 0			
			else 
				enqueue(dequeuedNode, &finishedQueue); // put it in finished queue when burst > 0	
		} 
		//If nothing in ready queue but there are still processes
		if(queueIsEmpty(&readyQueue) && !listIsEmpty(processList))
			currTime++;
		//If everything is already empty
		if (queueIsEmpty(&readyQueue) == 1 && listIsEmpty(processList) == 1) 
			finish = 1;
	}
	printRoundRobinResult(&finishedQueue);

}	