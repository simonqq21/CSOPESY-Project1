#include <stddef.h>
#include <stdlib.h>
#include "types.h"

// ProcessQueue* createProcessQueue(ProcessQueue *q) {
//     ProcessQueue * q = (ProcessQueue*) malloc (sizeof(ProcessQueue));
//     q -> head = q -> tail = NULL;
//     return q;
// };
//
// int enqueue(ProcessQueue *q, int pid, int arrival, int burst) {
//     Process_t *newProcess = malloc(sizeof(Process_t));
//     if(newProcess == NULL) {
//         return 0; //0 for false
//     } else {
//         newProcess->pid = pid;
//         newProcess->arrival = arrival;
//         newProcess->burst = burst;
//         newProcess->next = NULL;
//         Timeframe_t *timeframes = malloc(sizeof(timeframes));
//         newProcess->timeframes = timeframes; //check
//
//         //If there is existing tail connect
//         if (q->tail != NULL) {
//             q->tail->next = newProcess;
//         }
//         q->tail = newProcess; //new tail
//
//         //If queue is empty
//         if (q->head == NULL) {
//             q->head = newProcess; //point to new process
//         }
//         return 1; //return true
//     }
// }
//
// int dequeue(ProcessQueue *q) {
//
//     //Check if queue is empty
//     if(q->head == NULL)
//         return -999;
//     else {
//         //save head temporarily
//         Process_t *temp = q->head;
//         //get info from head
//         int pid = temp->pid;
//         int arrival = temp->arrival;
//         int burst = temp->burst;
//
//         //remove from list
//         q->head = q->head->next; //the node before it is the new head since FIFO
//         if (q->head == NULL) {
//             q->tail = NULL;
//         }
//         free(temp);
//     }
// }
//
// /* get the size of the queue */
// int queueSize
// /* get the process within a process queue with the minimum arrival time */
// int minIndex(ProcessQueue *q) {
//
// }
