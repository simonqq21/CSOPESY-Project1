typedef struct ProcessIDBurst {
	int pid;
	int origBurst;
} ProcessIDBurst;

void initProcessIDBurst(ProcessIDBurst processes[], Process_t *processList, int numProcesses);
void enqueue(Process_t *process, Queues *queue);
Process_t *dequeue(Queues *queue);
void enqueueArrivedProcesses(int *currTime, Process_t ** processList, Queues *queue, int *numProcesses);
Process_t *executeReadyQueue(Queues *readyQueue, int *currTime, int timeSlice, int *numProcess);
int queueIsEmpty(Queues *queue);
int listIsEmpty(Process_t *processList);
void printRoundRobinResult(Queues *queue);
extern void rr(Process_t *processList, int numProcesses, int timeSlice);
