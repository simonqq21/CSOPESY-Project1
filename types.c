#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "types.h"

Timeframe_t * createTimeframe(int start, int end) {

    Timeframe_t * t = NULL;
    t = (Timeframe_t *) malloc (sizeof(Timeframe_t));
    t->start = start;
    t->end = end;
    t->next = NULL;
    return t;
}

void printTimeframes(Timeframe_t * t) {
    Timeframe_t * current = t;
    while (current != NULL) {
        printf("start time: %d, end time: %d |", current->start, current->end);
        current=current->next;
    }
}

Process_t * createProcess(int pid, int arrival, int burst) {
    Process_t * p = NULL;
    p = (Process_t *) malloc (sizeof(Process_t));
    p->pid = pid;
    p->arrival=arrival;
    p->burst=burst;
    p->timeframes=NULL;
    p->next=NULL;
    return p;
}

void printProcess(Process_t * process) {
  int waitingTime = getProcessWaitingTime(process);
  if (process != NULL) {
    // for debugging
    if (process->burst > 0)
      printf("pid=%d, arrival=%d, burst=%d\n", process->pid, process->arrival, process->burst);
    else {
      printf("P[%d] ", process->pid);
      if (process->timeframes != NULL)
        printTimeframes(process->timeframes);

      // print waiting time
      if (waitingTime > -1)
        printf(" Waiting time: %d", waitingTime);
    }
  }

  else
    printf("NULL");
  printf("\n");
}

void printProcesses(Process_t * processes) {
    Process_t * current = processes;
    if (current == NULL)
        printf("no processes\n");
    else {
        do {
            printProcess(current);
            current=current->next;
        } while(current != NULL);
        float avgWaitingTime = getAverageWaitingTime(processes);
        if (avgWaitingTime > 0) {
          printf("Average waiting time: %0.1f", avgWaitingTime);
          printf("\n");
        }
    }

}


/* insert a process into the linked list of processes sorted according to arrival time
and PID ascending */
Process_t * insertProcess(Process_t ** processes, Process_t * p) {
    // if processes linked list is empty

    if (*processes == NULL) {
        *processes=p;
    }

    else {
        int newArrival = p->arrival;
        int newPid = p->pid;
        int firstArrival = (*processes)->arrival;
        int firstPid = (*processes)->pid;
        int nextArrival;
        int nextPid;
        // else if new process must be inserted before the head
        if (newArrival < firstArrival || (newArrival == firstArrival && newPid < firstPid)) {
            p->next = *processes;
            *processes = p;
        }

        // else, insert the new process before the process with a higher arrival time
        else {
            Process_t * current;
            current = *processes;
            if (current->next != NULL) {
                nextArrival = current->next->arrival;
                nextPid = current->next->pid;
            }
            while (current->next != NULL && (newArrival > nextArrival ||
              ( newArrival == nextArrival && newPid > nextPid))) {
                current = current->next;
                if (current->next != NULL) {
                    nextArrival = current->next->arrival;
                    nextPid = current->next->pid;
                }
            }
            if (current->next != NULL)
              p->next=current->next;
            current->next=p;
        }
    }

    return *processes;
}

// pop the first process from a list of processes
Process_t * popProcessFromBeginning(Process_t ** processes) {
  Process_t * p = NULL;
  if (*processes != NULL) {
    p = *processes;
    *processes = (*processes)->next;
  }
  if (p != NULL)
    p->next = NULL;
  return p;
}

// pop a process from a list of processes given a pid
Process_t * popProcessWithPid(Process_t ** processes, int pid) {
  // printf("X");
  Process_t * current = NULL;
  Process_t * p = NULL;
  int nextPid;

  // if processes is not empty
  if (*processes != NULL) {
    current = *processes;
    // if only one process and its PID matches
    if (current->pid == pid) {
      // printf("xs");
      p=current;
      if (current->next != NULL)
        *processes = (*processes)->next;
      else
        *processes = NULL;
    }
    // else if there is more than one process
    else if (current->next != NULL) {
      nextPid = current->next->pid;
      while (nextPid != pid && current->next != NULL) {
        current = current->next;
        if (current->next != NULL)
          nextPid = current->next->pid;
      }
      p = current->next;
      if (current->next != NULL) {
        // printf("d");
        current->next = current->next->next;
      }

    }
  }
  if (p != NULL)
    p->next = NULL;
  return p;
}

// get the length of a linked list of processes
int getProcessesLength(Process_t * processes) {
    int count = 0;
    Process_t * current = processes;
    while (current != NULL) {
      current=current->next;
      count+=1;
    }
    return count;
}

// add a timeframe to the timeframe linked list of a process
void addTimeFrameToProcess(Process_t ** process, Timeframe_t * timeframe) {
    if ((*process)->timeframes == NULL)
        (*process)->timeframes = timeframe;
    else {
        Timeframe_t * current = (*process)->timeframes;
        while (current->next != NULL)
          current = current->next;
        current->next = timeframe;
    }
}

// compute waiting time of a process
int getProcessWaitingTime(Process_t * p) {
  Timeframe_t * current = p->timeframes;
  int waiting = -1;
  if (current != NULL) {
    waiting = current->start - p->arrival;
    while(current->next != NULL) {
      waiting += current->next->start - current->end;
      current = current->next;
    }
  }
  return waiting;
}

// get average waiting time of a linked list of processes
float getAverageWaitingTime(Process_t * p) {
  Process_t * current = p;
  float sum = 0;
  float count = 0;
  while (current != NULL) {
    sum += getProcessWaitingTime(current);
    current=current->next;
    count++;
  }
  sum /= count;
  return sum;
}

void initQueue(Queues *q) {
    q->head = NULL;
    q->tail = NULL;
}

/*  This function deletes a specific process from the process list
    @param pid the process id to be deleted
    @param **processList pointer to the pointer to the head of the list of processes passed to the function
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