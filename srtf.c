#include <stdio.h>
#include "types.h"

Process_t * srtf(Process_t * processes, int processCount) {
	int time = 0;
	Process_t * readyProcesses = NULL;
	Process_t * newProcess = NULL;
	Process_t * executingProcess = NULL;
	Process_t * finishedProcesses = NULL;
	Timeframe_t * newtf = NULL;
	int shortestPid, prevShortestPid;
	int shortestBurst;
	Process_t * current;
	// time loop until there are no more processes
	while (executingProcess != NULL || processCount > 0 || readyProcesses != NULL) {
		// get processes that have arrived
		if (processes != NULL && processes->arrival <= time) {
			newProcess = popProcessFromBeginning(&processes);
			newProcess->next = NULL;
			if (newProcess != NULL) {
				readyProcesses= insertProcess(&readyProcesses, newProcess);
				processCount--;
			}
		}

		// return currently executing process to the ready queue
		if (executingProcess != NULL) {
			readyProcesses = insertProcess(&readyProcesses, executingProcess);
			executingProcess = NULL;
			newtf = NULL;
		}

		// get the pid of the process with the smallest remaining burst time
		shortestPid = -1;
		shortestBurst = 999999;
		current = readyProcesses;
		while (current != NULL) {
			if (current->burst < shortestBurst) {
				shortestPid = current->pid;
				shortestBurst = current->burst;
			}
			current = current->next;
		}

		// create new timeframe
		if (prevShortestPid != shortestPid || newtf == NULL) {
			// add timeframe to process before it is returned to ready queue
			executingProcess = popProcessWithPid(&readyProcesses, prevShortestPid);
			addTimeFrameToProcess(&executingProcess, newtf);
			readyProcesses = insertProcess(&readyProcesses, executingProcess);
			prevShortestPid = shortestPid;
			

			newtf = createTimeframe(time, time);
		}

		printProcesses(readyProcesses);
		// get the process with the smallest remaining burst time
		executingProcess = popProcessWithPid(&readyProcesses, shortestPid);
		printProcess(executingProcess);
		printf("short=%d\n", shortestPid);



		// execute one time unit of the current executing process
		if (executingProcess != NULL && executingProcess->burst > 0) {
			executingProcess->burst--;
			newtf->end++;
			time += 1;
		}

		// move finished process to finished processes list
		if (executingProcess->burst == 0) {
			finishedProcesses = insertProcess(&finishedProcesses, executingProcess);
			newtf = NULL;
		}
		printf("--------\n");
	}
	printf("\n");
	return finishedProcesses;
}
