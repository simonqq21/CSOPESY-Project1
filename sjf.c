#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "sjf.h"


void initQueue(Queues *q) {
    q->head = NULL;
    q->tail = NULL;
}

/*  This function deletes a specific process from the process list 
    @param pid the process id to be deleted
    @param *processList pointer to the head of the list of processes passed to the function
    @param numProcesses number of processes in the list of processes
*/
int deleteProcess(int pid, Process_t ** processList, int numProcesses) {
    Process_t *tmp = *processList;
    Process_t *nextNode;
    int found = 0;
    
    //if head will be deleted
    if(tmp->pid == pid) {
        *processList = tmp->next; //new head will be the head's next element
        if(*processList != NULL) //prevent garbage values from being printed
            free(tmp); 
        printf("Address of freed temp: %p\n", tmp);
        numProcesses = numProcesses - 1;
    } else {
        while (tmp != NULL && !found) {
            nextNode = tmp->next;
            if(nextNode->pid == pid) {
                tmp->next = nextNode->next;
                free(nextNode);
                numProcesses = numProcesses - 1;
                found = 1;
            }
            tmp = tmp->next;
        }
    }
    return numProcesses;
}
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
    @param *executedProcessList pointer to the head of the list of executed processes
*/
void enqueueAndExecuteProcess(Process_t *process, Queues *queue, int *currTime) {
    int start, end;
    Process_t *newnode = malloc(sizeof(Process_t));

    if(newnode == NULL) {
        printf("Memory not allocated.\n");
    } else {
        //Initialization of node to be enqueued
        newnode->pid = process->pid;
        newnode->arrival = process->arrival;
        newnode->burst = process->burst;
        newnode->next = NULL;
        start = *currTime;
        end = start + newnode->burst;
        *currTime = end;
        newnode->timeframes = createTimeframe(start, end);
        //Previous tail connects to new node
        if(queue->tail != NULL) {
            queue->tail->next = newnode;
        }
        queue->tail = newnode; //newnode is the new tail
        //If currently no head
        if (queue->head == NULL) {
            queue->head = newnode;
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
    printf("Average waiting time: %f\n", aveWaiting);
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
