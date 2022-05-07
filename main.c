#include <stdio.h>
#include <stdlib.h>

int main() {

  char fileName[100];
  FILE *fp; //file pointer
  int nSchedAlgo, y, z;

  printf("Input the name of the input text file: ");
  scanf("%s", fileName);
  fp = fopen(fileName, "r");

  if (fp != NULL) {
    printf("File found!");
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
    printf("%s not found.", fileName);
  }

  return 0;
}
