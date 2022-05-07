#include <stdio.h>
#include <stdlib.h>

int main() {

  char fileName[100];
  FILE *fp; //file pointer
  int nSchedAlgo, y, z;
  int a, b, c;
  // printf("Input the name of the input text file: ");
  // scanf("%s", fileName);
  // fp = fopen(fileName, "r");
  fp = fopen("test.txt", "r");

  if (fp != NULL) {
  //get number to see if scheduling algo
    fscanf(fp, "%d %d %d", &nSchedAlgo, &y, &z);
    printf("Numbers from file: %d, %d, %d\n", nSchedAlgo, y, z);
    //if FCFS
    if(nSchedAlgo == 0) {
      printf("FCFS algorithm will be performed");
    } 
    //if SJF
    else if(nSchedAlgo == 1) {
      printf("SJF algorithm will be performed");
    }
    //if SRTF
    else if (nSchedAlgo == 2) {
      printf("SRTF algorithm will be performed");
    }
    //if RR
    else if (nSchedAlgo == 3) {
      printf("RR algorithm will be performed");
    }
    
    //convert to integer
    //check if valid input
  } else {
    printf("%s not found.", fileName);
  }
  
  fclose(fp);
  return 0;
}
