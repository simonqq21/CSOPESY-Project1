/* Each job has a pid, burst time, and arrival time. Each job also has a
dynamically allocated array of timeframes. */
// Each timeframe has a start time and an end time.
// Sort the jobs based on arrival time in ascending order

typedef struct Timeframe {
	int start;
	int end;
	struct Timeframe * next;
} Timeframe_t;

typedef struct Process{
	int pid;
	int arrival;
	int burst;
	Timeframe_t * timeframes;
	struct Process * next;
} Process_t;

typedef struct Queues {
    Process_t *head;
    Process_t *tail;
} Queues;

Timeframe_t * createTimeframe(int start, int end);
void printTimeframes(Timeframe_t * t);
Process_t * createProcess(int pid, int arrival, int burst);
void printProcesses(Process_t * processes);
Process_t * insertProcess(Process_t ** processes, Process_t * p);
void addTimeFrameToProcess(Process_t ** process, Timeframe_t * timeframe);
void printProcess(Process_t * process);
Process_t * popProcessFromBeginning(Process_t ** processes);
int getProcessesLength(Process_t * processes);
int getProcessWaitingTime(Process_t * p);
float getAverageWaitingTime(Process_t * p);
Process_t * popProcessWithPid(Process_t ** processes, int pid);
void initQueue(Queues *q);
int deleteProcess(int pid, Process_t **processList, int numProcesses);