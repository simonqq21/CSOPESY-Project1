#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "fcfs.h"
#include "sjf.h"
#include "srtf.h"
#include "rr.h"

int main() {
  char fileName[100];
  FILE *fp; //file pointer
  int nSchedAlgo, processCount, timeSlice; // variables for first line
  int currPid, currArrvTime, currBurstTime;
  Process_t processes[100];
  ProcessQueue * processQueue = createProcessQueue();
  ProcessQueue * readyQueue = createProcessQueue();

  printf("Input the name of the input text file: ");
  scanf("%s", fileName);
  fp = fopen(fileName, "r");

  if (fp != NULL) {
    //get number to see if scheduling algo
    fscanf(fp, "%d %d %d", &nSchedAlgo, &processCount, &timeSlice);
    printf("Numbers from file: %d, %d, %d\n", nSchedAlgo, processCount, timeSlice);

    // read each process
    while(!feof(fp)) {
      fscanf(fp, "%d %d %d\n", &currPid, &currArrvTime, &currBurstTime);
      printf("%d %d %d\n", currPid, currArrvTime, currBurstTime);
    }

    switch (nSchedAlgo) {
      //if FCFS
      case 0:
        printf("FCFS algorithm will be performed\n");
        fcfs(processes);
        break;
      //if SJF
      case 1:
        printf("SJF algorithm will be performed\n");
        sjf(processes);
        break;
      //if SRTF
      case 2:
        printf("SRTF algorithm will be performed\n");
        srtf(processes);
        break;
      //if RR
      case 3:
        printf("RR algorithm will be performed\n");
        rr(processes);
        break;
    }

    fclose(fp);
  } else {
    printf("%s not found.\n", fileName);
  }

  return 0;
}
