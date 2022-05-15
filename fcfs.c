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
	printProcesses(processes);
	// time loop until there are no more processes
	while (executingProcess != NULL || processCount > 0) {
		// printf("%d\n", processCount);
		// get processes that have arrived
		if (processes != NULL && processes->arrival <= time) {
			newProcess = popProcessFromBeginning(&processes);
			newProcess->next = NULL;
			if (newProcess != NULL) {
				readyProcesses= insertProcess(&readyProcesses, newProcess);
				processCount--;
			}
			printProcesses(readyProcesses);
			printf("--------\n");
		}

		// create new timeframe
		if (newtf == NULL) {
			newtf = createTimeframe(time, time);
		}

		if (executingProcess == NULL) {
			executingProcess = popProcessFromBeginning(&readyProcesses);

		}
		// execute one time unit of the current executing process
		else if (executingProcess->burst > 0) {
			executingProcess->burst--;
			newtf->end++;
			time += 1;
		}

		// move finished process to finished processes list
		else if (executingProcess->burst == 0) {
			printTimeframes(newtf);
			addTimeFrameToProcess(&executingProcess, newtf);
			finishedProcesses = insertProcess(&finishedProcesses, executingProcess);
			executingProcess = popProcessFromBeginning(&readyProcesses);
			newtf = NULL;
		}
	}

	printf("\n");
	return finishedProcesses;
}
