#include <stdio.h>
#include <stdlib.h>
#include "types.h"

Process_t * fcfs(Process_t * processes, int processCount) {
	int time = 0;
	Process_t * readyProcesses = NULL;
	Process_t * newProcess = NULL;
	Process_t * executingProcess = NULL;
	Process_t * finishedProcesses = NULL;
	Timeframe_t * newtf = NULL;
	// time loop until there are no more processes
	while (executingProcess != NULL || processCount > 0) {
		// get processes that have arrived
		if (processes != NULL && processes->arrival <= time) {
			// printf("x");
			newProcess = popProcessFromBeginning(&processes);
			// printf("p");
			newProcess->next = NULL;
			if (newProcess != NULL) {
				readyProcesses= insertProcess(&readyProcesses, newProcess);
				processCount--;
			}
			printProcesses(readyProcesses);
		}

		// create new timeframe
		if (newtf == NULL) {
			printf("T");
			newtf = createTimeframe(time, time);
		}
		//
		// if (executingProcess == NULL) {
		// 	executingProcess = popProcessFromBeginning(&readyProcesses);
		// }
		// move finished process to finished processes list
		// else if (executingProcess->burst == 0) {
		// 	addTimeFrameToProcess(&executingProcess, newtf);
		// 	finishedProcesses = insertProcess(&finishedProcesses, executingProcess);
		// 	executingProcess = popProcessFromBeginning(&readyProcesses);
		// 	newtf = NULL;
		// }
		// execute one time unit of the current executing process
		// else if (executingProcess->burst > 0) {
		// 	executingProcess->burst--;
		// 	newtf->end++;
		// }
		// current = readyProcesses;
		// while (current != NULL) {
		// 	if (current->burst > 0) {
		//
		// 	}
		// 	current = current->next;
		// }
		time += 1;
	}

	printf("\n");
	printf("%d", time);
	return finishedProcesses;
}
