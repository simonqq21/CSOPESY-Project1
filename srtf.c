#include <stdio.h>
#include "types.h"

Process_t * srtf(Process_t * processes, int processCount) {
	int time = 0;
	Process_t * readyProcesses = NULL;
	Process_t * newProcess = NULL;
	Process_t * executingProcess = NULL;
	Process_t * finishedProcesses = NULL;
	Timeframe_t * newtf = NULL;
	int shortestPid;
	int shortestBurst;
	Process_t * current;
	// time loop until there are no more processes
	while (executingProcess != NULL || processCount > 0) {
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
		}

		// get the process with the smallest remaining burst time
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
		printProcesses(readyProcesses);
		printf("short=%d\n", shortestPid);
		printProcess(executingProcess);
		executingProcess = popProcessWithPid(&readyProcesses, shortestPid);
		printProcess(executingProcess);
		printf("short=%d\n", shortestPid);

		// create new timeframe
		if (newtf == NULL) {
			newtf = createTimeframe(time, time);
		}

		// execute one time unit of the current executing process
		if (executingProcess != NULL && executingProcess->burst > 0) {
			executingProcess->burst--;
			newtf->end++;
			time += 1;
		}

		// move finished process to finished processes list
		// if (executingProcess->burst == 0) {
		// 	addTimeFrameToProcess(&executingProcess, newtf);
		// 	finishedProcesses = insertProcess(&finishedProcesses, executingProcess);
		// 	executingProcess = popProcessFromBeginning(&readyProcesses);
		// 	newtf = NULL;
		// }
	}
	printf("\n");
	return finishedProcesses;
}
