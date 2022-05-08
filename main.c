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
        fcfs(processes);
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
