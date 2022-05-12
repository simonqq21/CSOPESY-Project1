#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "sjf.h"

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

/*This function deletes a specific process from the process list */
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
/* This function searches the shortest burst process that has already arrived */
Process_t *searchArrivedShortestProcess (int currTime, Process_t *processList) {
    Process_t *tmp = processList;
    Process_t *minProcess = NULL;
    int minBurst;

    minBurst = tmp->burst;
    //Traverse through the process list
    while (tmp != NULL) {
         //Search for the processes <= current time and insert them to the waiting list, deleting inserted ones from the process list
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

/* Main function that performs SJF */
void sjf(Process_t *processList, int numProcesses) {
    int currTime = 0;
    //Process_t *waitingList = malloc(sizeof(Process_t)); //head of waiting list
    Process_t *executedProcessHead = malloc(sizeof(Process_t)); //head of executed
    Process_t *temp;
    printf("[Delete me] SJF ALGO will be performed\n");
    printf("[Delete me] Num of processes: %d\n", numProcesses);

    if(executedProcessHead == NULL) {
        printf("Memory is not allocated.\n");
    } else {
        while(numProcesses > 0) {
            temp = searchArrivedShortestProcess(currTime, processList);
            if(temp != NULL) {
                printf("Minprocess: %d", temp->burst);
                numProcesses = deleteProcess(temp->pid, processList, numProcesses);
                printProcesses(processList);
                //insert to executedProcess (where calculation of time frame is done)
                //delete the process from the process list, using temp as reference or temp->pid
            } else {
                printf("[Delete me] No process has arrived yet at time %d.\n", currTime);
            }
            currTime++;
            // currProcess = searchShortestBurst(waitingList);
            // currProcess->timeframes->start = currTime;
            // currProcess->timeframes->end = currProcess->timeframes->start + currProcess->burst;
            // currTime = currProcess->timeframes->end;
            // insertCompleteJobs(currTime);
            // numProcesses = numProcesses - 1; 
        }
    }
    
}
