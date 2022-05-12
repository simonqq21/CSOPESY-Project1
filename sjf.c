#include <stdio.h>
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
void insertToWaitList (Process_t *arrivedProcess, Process_t *waitingListHead) {
    Process_t *newProcess = malloc(sizeof(Process_t));

    if(newProcess == NULL) {
        return 0; //0 for false
    } else {
        *newProcess = *arrivedProcess; //copy the contents

        //If list is empty
        if(waitingListHead == NULL) {
            waitingListHead = newProcess;
            waitingListHead->next = NULL;
        } else {

        }
        //If there is existing tail connect 
        if (q->tail != NULL) {
            q->tail->next = newProcess; 
        }
        q->tail = newProcess; //new tail 

        //If queue is empty
        if (q->head == NULL) {
            q->head = newProcess; //point to new process
        }
        return 1; //return true
    }
}

void searchArrivedProcess (int currTime, Process_t *processList, Process_t *waitingList) {
    //Search for the processes <= current time and insert them to the waiting list, deleting inserted ones from the process list
    Process_t *tmp = processList;
    //Traverse through the process list
    while (tmp != NULL) {
        if (tmp->arrival <= currTime) {
            insertToWaitList(tmp, waitingList);
            //sortwaitinglist to shortest burst time
            //then just 
            //deleteNodeFromList(processList, tmp->pid);
        }
        tmp = tmp->next;
    }
}

// /* For checking purposes */
void printList(Process_t *head) {
    Process_t *tmp = head;
    while(tmp != NULL) {
        printf("Pid: %d, AT: %d, BT: %d\n", tmp->pid, tmp->arrival, tmp->burst);
        tmp = tmp->next; 
    }
}

/* Main function that performs SJF */
void sjf(Process_t *processList, int numProcesses) {
    printf("SJF ALGO\n");
    int currTime = 0;
    Process_t *waitingListHead = malloc(sizeof(Process_t));
    Process_t *executedProcessHead = malloc(sizeof(Process_t));
    printf("Num of processes: %d", numProcesses);
    while(numProcesses > 0) {
        searchArrivedProcess(currTime, processList);
        // currProcess = searchShortestBurst(waitingList);
        // currProcess->timeframes->start = currTime;
        // currProcess->timeframes->end = currProcess->timeframes->start + currProcess->burst;
        // currTime = currProcess->timeframes->end;
        // insertCompleteJobs(currTime);
        // numProcesses = numProcesses - 1; 
    }

    
}
