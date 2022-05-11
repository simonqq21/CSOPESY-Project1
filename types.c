#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "types.h"

Timeframe_t * createTimeframe(int start, int end) {
  Timeframe_t * t = (Timeframe_t *) malloc (sizeof(Timeframe_t*));
  t->start = start;
  t->end = end;
  t->next=NULL;
  return t;
}

Process_t * createProcess(int pid, int arrival, int burst) {
    Process_t * p = (Process_t *) malloc (sizeof(Process_t*));
    p->pid = pid;
    p->arrival=arrival;
    p->burst=burst;
    p->timeframes=NULL;
    p->next=NULL;
    return p;
}

void printProcesses(Process_t * processes) {
  Process_t * current = processes;
    do {
      printf("pid=%d, arrival=%d, burst=%d", current->pid, current->arrival, current->burst);
      current=current->next;
    } while(current != NULL);
}

/* insert a process into the linked list of processes sorted according to arrival time
ascending */
Process_t * insertProcess(Process_t * processes, Process_t * p) {
  int newArrival = p->arrival;
  int firstArrival = processes->arrival;
  int arrival;
  printf("%d\n", newArrival);
  printf("%d\n", firstArrival);
  printf("%d\n", arrival);
  // // if processes linked list is empty
  // if (processes == NULL)
  //   processes=p;
  //
  // // else if new process must be inserted before the head
  // else if (newArrival < firstArrival) {
  //   p->next = processes;
  //   processes = p;
  // }
  //
  // // else, insert the new process before the process with a higher arrival time
  // else {
  //   Process_t * current;
  //   current = processes->next;
  //   arrival = current->arrival;
  //   while (current != NULL || arrival<=newArrival) {
  //     current = current->next;
  //     arrival = current->arrival;
  //   }
  //   if (current != NULL) {
  //     p->next=current->next;
  //     current->next=p;
  //   }
  // }
  return processes;
}



void addTimeFrameToProcess(Process_t * process, Timeframe_t * timeframe) {
  if (process->timeframes == NULL)
    process->timeframes = timeframe;
  else {
    Timeframe_t * current = process->timeframes->next;
    while (current != NULL)
      current = current->next;
    current = timeframe;
  }
}

// int addProcess(Process_t * process, )
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





// processes from file will be read one at a time
// once a process is read, it will be inserted in its sorted location in the linked list
