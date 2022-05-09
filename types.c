#include <stddef.h>
#include <stdlib.h>
#include "types.h"

ProcessQueue* createProcessQueue(void) {
  ProcessQueue * q = (ProcessQueue*) malloc (sizeof(ProcessQueue));
  q -> head = q -> tail = NULL;
  return q;
};
