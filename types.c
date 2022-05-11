#include <stddef.h>
#include <stdlib.h>
#include "types.h"

Process_t* createProcess(int pid, int arrival, int burst) {
  Process_t p = (Process_t*) malloc (sizeof(Process_t*));
  p -> pid = pid;
  p -> 
};

ProcessQueue* createProcessQueue(void) {
  ProcessQueue * q = (ProcessQueue*) malloc (sizeof(ProcessQueue));
  q -> head = q -> tail = NULL;
  return q;
};
