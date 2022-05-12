int deleteProcess(int pid, Process_t *processList, int numProcesses);
Process_t *searchArrivedShortestProcess (int currTime, Process_t *processList);
extern void sjf(Process_t *processList, int numProcesses);
