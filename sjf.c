#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "sjf.h"


void initQueue(Queues *q) {
    q->head = NULL;
    q->tail = NULL;
}
// Process_t *searchShortestBurst (Process_t *head) {
//     Process_t *tmp = head;
//     Process_t *minProcessBurst = NULL;
//     int nFound = 0;
//     int minBurst;

//     minBurst = tmp->burst;
//     printf("[DELETE ME] Current minBurst: %d\n", minBurst);
//     while(tmp != NULL) {
//         if(tmp->burst < minBurst) {
//             minBurst = tmp->burst;
//             minProcessBurst = tmp;
//         }
//         tmp = tmp->next; 
//     }
//     printf("[DELETE ME] PID %d \n Process Burst: %d\n Minburst: %d \n\n", minProcessBurst->pid, minProcessBurst, minBurst);
//     return minProcessBurst;
// }

// void *deleteProcess(process_t *) {

// }

// /* This function is to remove process that is in the linked list of arrived processes */
// void removeProcess(Process_t *head, int pid) {
//     //Fix the links
//     //Free the space
//     Process_t *tmp = head;
//     int nFound = 0;
//     //if Process to be removed is the head
//     if (head->pid = pid) {
//         head = tmp->next;
//         free(tmp);
//     }
//     while(tmp != NULL && !nFound) {
//         if(tmp->pid == pid) {
//             tmp
//             nFound = 1;
//         } 
//         tmp = tmp->next;
//     }


// }

// /* This function inserts to the waiting list when time is */
// void insertToWaitList (Process_t *arrivedProcess, Process_t *waitingListHead) {
//     Process_t *newProcess = malloc(sizeof(Process_t));

//     if(newProcess == NULL) {
//         printf("Memory not allocated.\n");
//     } else {
//         *newProcess = *arrivedProcess; //copy the contents

//         //If list is empty
//         if(waitingListHead == NULL) {
//             waitingListHead = newProcess;
//             waitingListHead->next = NULL;
//         } else {

//         }
//         //If there is existing tail connect 
//         if (q->tail != NULL) {
//             q->tail->next = newProcess; 
//         }
//         q->tail = newProcess; //new tail 

//         //If queue is empty
//         if (q->head == NULL) {
//             q->head = newProcess; //point to new process
//         }
//         return 1; //return true
//     }
// }

/*  This function deletes a specific process from the process list 
    @param pid the process id to be deleted
    @param *processList pointer to the head of the list of processes passed to the function
    @param numProcesses number of processes in the list of processes
*/
int deleteProcess(int pid, Process_t *processList, int numProcesses) {
    Process_t *tmp = processList;
    Process_t *nextNode;
    int found = 0;

    //if head will be deleted
    if(tmp->pid == pid) {
        processList = tmp->next; //new head will be the head's next element
        free(tmp);
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
    Process_t *minProcess = NULL;
    int minBurst;

    minBurst = tmp->burst;
    
    //Traverse through the process list
    while (tmp != NULL) {
         //Search for the processes <= current time and insert them to the waiting list, deleting inserted ones from the process list
        printf("[delete me] P[%d] arrival time: %d, burst time: %d\n", tmp->pid, tmp->arrival, tmp->burst);
        if (tmp->arrival <= currTime && tmp->burst < minBurst) {
            //Allocate memory to be able to copy files if not done yet
            if(minProcess == NULL) {
                minProcess = malloc(sizeof(Process_t));
            }
            *minProcess = *tmp;
            minBurst = tmp->burst;
        }
        tmp = tmp->next;
    }
    return minProcess;
}

// /* For checking purposes */
// void printList(Process_t *head) {
//     Process_t *tmp = head;
//     while(tmp != NULL) {
//         printf("[Delete me] Pid: %d, AT: %d, BT: %d\n", tmp->pid, tmp->arrival, tmp->burst);
//         tmp = tmp->next; 
//     }
// }

/*  This function enqueues the shortest burst arrived process to another list and 
    executes by adjusting Timeframe parameters
    @param process the process to be executed and inserted in list of executed processes
    @param *executedProcessList pointer to the head of the list of executed processes
*/
void enqueueAndExecuteProcess(Process_t *process, Queues *queue, int *currTime) {
    Process_t *newnode = malloc(sizeof(Process_t));

    if(newnode == NULL) {
        printf("Memory not allocated.\n");
    } else {
        //Initialization of node to be enqueued
        newnode->arrival = process->arrival;
        newnode->burst = process->burst;
        newnode->timeframes = process->timeframes;
        newnode->next = NULL;

        newnode->timeframes->start = *currTime;
        newnode->timeframes->end = newnode->timeframes->start + newnode->burst;
        *currTime = newnode->timeframes->end;

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

// /*  This function dequeues a process and returns the process for printing
//     @param *queue points to the queue
// */
// void printExecuted(Queues *queue) {
//     Process_t *temp = queue->head;
//     while(queue->head != NULL) {
//          Process_t result = *temp;
//         //Save new head of queue
//         queue->head = queue->head->next;
//         //if no more nodes
//         if (queue->head == NULL) {
//             queue->tail = NULL;
//         }
//         free(temp);
//         printf("P[%d] Start Time: %d End time: %d | Waiting time: %d\n");
//         printf("Average waiiting time: %f");
//     }
   
// }

/*  Main function that performs SJF 
    @param *processList pointer to the head of the list of processes passed to the function
    @param numProcesses number of processes in the list according to input from file
*/
void sjf(Process_t *processList, int numProcesses) {
    int currTime = 0;
    //Process_t *waitingList = malloc(sizeof(Process_t)); //head of waiting list
    Process_t *temp;
    Queues executedQueue;
    
    initQueue(&executedQueue); //to store the executed processes
    printf("\n\n-----[Delete me] SJF ALGO will be performed\n");
    printf("[Delete me] Num of processes: %d\n", numProcesses);

    while(numProcesses > 0) {
        temp = searchArrivedShortestProcess(currTime, processList);
        if(temp != NULL) {
            printf("Minprocess: %d\n", temp->burst);
            enqueueAndExecuteProcess(temp, &executedQueue, &currTime);
            numProcesses = deleteProcess(temp->pid, processList, numProcesses);
            printProcesses(processList);
            printf("-------------\n");
            
        } else {
            printf("-------------\n");
            printf("[Delete me] No process has arrived yet at time %d.\n\n", currTime);
            printf("-------------\n");
        }
        currTime++;
        
    }
    printf("\n\n\nNum processes left: %d", numProcesses);

    
}
