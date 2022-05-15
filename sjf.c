#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "sjf.h"


/*  This function searches the shortest burst process that has already arrived
    @param currTime current unit time of process execution
    @param *processList pointer to the head of the list of processes passed to the function
*/
Process_t *searchArrivedShortestProcess (int currTime, Process_t *processList) {
    Process_t *tmp = processList;
    Process_t *minProcess = (Process_t *) malloc(sizeof(Process_t));
    *minProcess = *processList;
    //Traverse through the process list
    while (tmp != NULL) {
         //Search for the processes <= current time and insert them to the waiting list, deleting inserted ones from the process list
        if (tmp->arrival <= currTime && tmp->burst < minProcess->burst) {
            //Allocate memory to be able to copy files if not done yet
            *minProcess = *tmp;
        }
        tmp = tmp->next;
    }
    return minProcess;
}



/*  This function enqueues the shortest burst arrived process to another list and 
    executes by adjusting Timeframe parameters
    @param process the process to be executed and inserted in list of executed processes
    @param *queue pointer to the head of the list of executed processes
    @param *currTime pointer to the variable containing the current unit time of process execution
*/
void enqueueAndExecuteProcess(Process_t *process, Queues *queue, int *currTime) {
    int start, end;
    Process_t *newProcess = malloc(sizeof(Process_t));

    if(newProcess == NULL) {
        printf("Memory not allocated.\n");
    } else {
        //Initialization of node to be enqueued
        newProcess->pid = process->pid;
        newProcess->arrival = process->arrival;
        newProcess->burst = process->burst;
        newProcess->next = NULL;
        start = *currTime;
        end = start + newProcess->burst;
        *currTime = end;
        newProcess->timeframes = createTimeframe(start, end);
        //Previous tail connects to new node
        if(queue->tail != NULL) {
            queue->tail->next = newProcess;
        }
        queue->tail = newProcess; //newProcess is the new tail
        //If currently no head
        if (queue->head == NULL) {
            queue->head = newProcess;
        }
    }
}

/*  This function dequeues a process and returns the process for printing
    @param *queue points to the queue
*/
void printExecutedQueue(Queues *queue) {
    Process_t *temp;
    int waitingTime = 0;
    float aveWaiting = 0;
    aveWaiting = getAverageWaitingTime(queue->head);
    // int turnAround = 0;
    while(queue->head != NULL) {
        temp = queue->head;
        // turnAround = temp->timeframes->end - temp->arrival;
        waitingTime = getProcessWaitingTime(temp);
        printf("P[%d] Start Time: %d End time: %d | Waiting time: %d\n", temp->pid, temp->timeframes->start, temp->timeframes->end, waitingTime);
        //Save new head of queue 
        queue->head = queue->head->next;
        //if no more nodes
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        free(temp);
    }
    printf("Average waiting time: %.1f\n", aveWaiting);
}

/*  Main function that performs SJF 
    @param *processList pointer to the head of the list of processes passed to the function
    @param numProcesses number of processes in the list according to input from file
*/
void sjf(Process_t *processList, int numProcesses) {
    int currTime = 0; //used to see which processes arrived
    //Process_t *waitingList = malloc(sizeof(Process_t)); //head of waiting list
    Process_t *temp;
    Queues executedQueue;
    
    initQueue(&executedQueue); //to store the executed processes

    while(numProcesses > 0) {
        temp = searchArrivedShortestProcess(currTime, processList);
        if(temp != NULL &&  temp->arrival <= currTime) {
            enqueueAndExecuteProcess(temp, &executedQueue, &currTime);
            numProcesses = deleteProcess(temp->pid, &processList, numProcesses);
            printProcesses(processList);
        } else {
            if(temp != NULL) 
                free(temp); //free process that will not be used anymore   
            currTime++;
        }
    }
    printExecutedQueue(&executedQueue); 
    
}
