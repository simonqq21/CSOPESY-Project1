void initQueue(Queues *q);
Process_t *searchArrivedShortestProcess (int currTime, Process_t *processList);
void enqueueAndExecuteProcess(Process_t *process, Queues *queue, int *currTime);
extern void sjf(Process_t *processList, int numProcesses);
