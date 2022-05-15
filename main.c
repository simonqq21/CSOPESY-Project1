#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "fcfs.h"
#include "sjf.h"
#include "srtf.h"
#include "rr.h"

/* This function is used to return if the process count or the time slice is a valid input */
int isValidInput(int processCount, int timeSlice) {
	int result = 0;
	if((3 <= processCount && processCount <= 100) && (1 <= timeSlice && timeSlice <= 100))
		result = 1;
	else
		result = 0;
	return result;
}

int main() {
	char fileName[100];
	FILE *fp; //file pointer
	int nSchedAlgo, processCount, timeSlice; // variables for first line
	int pid, arrival, burst;
	Process_t *processes = NULL;
	Process_t *resultingProcesses;
	int validInput = 0;
	int count = 0;

	printf("Input the name of the input text file: ");
	scanf("%s", fileName);
	// for testing
	// strcpy(fileName, "exercise1_3.txt");
	fp = fopen(fileName, "r");

	if (fp != NULL) {
		fscanf(fp, "%d %d %d", &nSchedAlgo, &processCount, &timeSlice);
		if(nSchedAlgo != 3)
			timeSlice = 1;
		validInput = isValidInput(processCount, timeSlice);
		if(validInput) {
			while(!feof(fp) && count < processCount) {
				fscanf(fp, "%d %d %d\n", &pid, &arrival, &burst);
				Process_t *tP = NULL;
				tP = createProcess(pid, arrival, burst);
				processes = insertProcess(&processes, tP);

				count++;
			}
			processCount = count; //in case number of processes do not match the one from the input

			switch (nSchedAlgo) {
			//if FCFS
			case 0:
				printf("FCFS algorithm will be performed\n");
				resultingProcesses = fcfs(processes, processCount);
				printProcesses(resultingProcesses);
				// Process_t * tp;
				// for (int i=0;i<10;i++) {
				//
				// 	printProcesses(processes);
				// 	printf("%d\n", getProcessesLength(processes));
				// 	tp = popProcessFromBeginning(&processes);
				// 	printProcess(tp);
				// }
				break;
			//if SJF
			case 1:
				sjf(processes, processCount);
				break;
			break;
			//if SRTF
			case 2:
				printf("SRTF algorithm will be performed\n");
				resultingProcesses = srtf(processes, processCount);
				printProcesses(resultingProcesses);
				break;
			//if RR
			case 3:
				rr(processes, processCount, timeSlice);
				break;
		}
			fclose(fp);
		} else {
			printf("Invalid input has been found in the first line of the text file. Try again.\n");
		}
	} else {
		printf("%s not found.\n", fileName);
	}

  	return 0;
}
