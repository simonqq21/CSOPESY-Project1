#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "fcfs.h"
#include "sjf.h"
#include "srtf.h"
#include "rr.h"
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
	Process_t * processes;
	int validInput = 0;
	int count = 0;
	// printf("Input the name of the input text file: ");
	// scanf("%s", fileName);
	// for testing
	strcpy(fileName, "sample4.txt");
	fp = fopen(fileName, "r");

	if (fp != NULL) {
		fscanf(fp, "%d %d %d", &nSchedAlgo, &processCount, &timeSlice);
		printf("Numbers from file: %d, %d, %d\n", nSchedAlgo, processCount, timeSlice);
		validInput = isValidInput(processCount, timeSlice); 
		if(validInput) {
			while(!feof(fp) && count < processCount) {
				fscanf(fp, "%d %d %d\n", &pid, &arrival, &burst);
				Process_t * tP;
				tP = createProcess(pid, arrival, burst);
				printf("HELLO: %d %d %d\n", tP->pid, tP->arrival, tP->burst);
				// printProcess(tP);
				processes = insertProcess(&processes, tP);
				printProcesses(processes);
				count++;
			}
			printf("\n----Printing Processes----\n");
			printProcesses(processes);

		switch (nSchedAlgo) {
			//if FCFS
			case 0:
				printf("FCFS algorithm will be performed\n");
				fcfs(processes);
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
				printf("SJF algorithm will be performed\n");
				sjf(processes, processCount);
			break;
			//if SRTF
			case 2:
				printf("SRTF algorithm will be performed\n");
				sjf(processes);
			break;
			//if RR
			case 3:
				printf("RR algorithm will be performed\n");
				rr(processes);
			break;
		}

			fclose(fp);
		} else {
			printf("Invalid input has been found in the first line of the text file. Try again.");
		}
	} else {
		printf("%s not found.\n", fileName);
	}

  	return 0;
}
