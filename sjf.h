typedef struct Queues {
    Process_t *head;
    Process_t *tail;
} Queues;

void initQueue(Queues *q);
int deleteProcess(int pid, Process_t **processList, int numProcesses);
Process_t *searchArrivedShortestProcess (int currTime, Process_t *processList);
void enqueueAndExecuteProcess(Process_t *process, Queues *queue, int *currTime);
extern void sjf(Process_t *processList, int numProcesses);
