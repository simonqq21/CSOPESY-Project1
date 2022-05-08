#include <stdio.h>
#include <stdlib.h>


/* Each job has a pid, burst time, and arrival time. Each job also has a
dynamically allocated array of timeframes. */
// Each timeframe has a start time and an end time.
// Sort the jobs based on arrival time in ascending order

typedef struct Timeframe {
  int start;
  int end;
  struct Timeframe * next;
} Timeframe_t;

typedef struct Process {
  int pid;
  int arrival;
  int burst;
  Timeframe_t * timeframe
} Process_t;


int main() {

  char fileName[100];
  FILE *fp; //file pointer
  int nSchedAlgo, y, z; // variables for first line
  Process_t processes[100];

  printf("Input the name of the input text file: ");
  scanf("%s", fileName);
  fp = fopen(fileName, "r");

  if (fp != NULL) {
    //get number to see if scheduling algo
    fscanf(fp, "%d %d %d", &nSchedAlgo, &y, &z);
    printf("Numbers from file: %d, %d, %d\n", nSchedAlgo, y, z);
    switch (nSchedAlgo) {
      //if FCFS
      case 0:
        printf("FCFS algorithm will be performed");
        break;
      //if SJF
      case 1:
        printf("SJF algorithm will be performed");
        break;
      //if SRTF
      case 2:
        printf("SRTF algorithm will be performed");
        break;
      //if RR
      case 3:
        printf("RR algorithm will be performed");
        break;
    }

    //check if valid input
    // while(!feof(fp)) {
    //
    // }
    fclose(fp);
  } else {
    printf("%s not found.\n", fileName);
  }

  return 0;
}
