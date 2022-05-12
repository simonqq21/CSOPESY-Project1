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
		printProcesses(readyProcesses);
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
		// return currently executing process
		if (executingProcess != NULL) {
			readyProcesses = insertProcess(&readyProcesses, executingProcess);
		}
		printf("short=%d\n", shortestPid);
		executingProcess = popProcessWithPid(&readyProcesses, shortestPid);
		printProcess(executingProcess);
	// 	printProcesses(processes);
	//
	//
	//
	// 	// create new timeframe
	// 	if (newtf == NULL) {
	// 		newtf = createTimeframe(time, time);
	// 	}
	//
		if (executingProcess == NULL) {
			executingProcess = popProcessFromBeginning(&readyProcesses);

		}
		// execute one time unit of the current executing process
		// else if (executingProcess->burst > 0) {
		// 	executingProcess->burst--;
		// 	newtf->end++;
			time += 1;
		// }
	//
	// 	// move finished process to finished processes list
	// 	else if (executingProcess->burst == 0) {
	// 		addTimeFrameToProcess(&executingProcess, newtf);
	// 		finishedProcesses = insertProcess(&finishedProcesses, executingProcess);
	// 		executingProcess = popProcessFromBeginning(&readyProcesses);
	// 		newtf = NULL;
	// 	}
	}
	printf("\n");
	return finishedProcesses;
}
