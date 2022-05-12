#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void fcfs(Process_t * processes) {

	int time = 0;
	Process_t * readyProcesses = NULL;
	Process_t * newProcess = NULL;
	while (getProcessesLength(processes) > 0) {
		// printf("%d\n", processes->arrival);
		if (processes->arrival <= time) {
			newProcess = popProcessFromBeginning(&processes);
			newProcess->next = NULL;
			if (newProcess != NULL)
				readyProcesses= insertProcess(&readyProcesses, newProcess);
				printProcesses(readyProcesses);
		}

		time += 1;
	}
	printf("\n");
	printf("%d", time);

}
