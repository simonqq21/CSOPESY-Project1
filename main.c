#include <stdio.h>
#include <stdlib.h>

int main() {

  char fileName[100];
  FILE *fp; //file pointer

  printf("Input the name of the input text file: ");
  scanf("%s", fileName);
  fp = fopen(fileName, "r");

  if (fp != NULL) {
    printf("File found!");
    while(!feof(fp)) {
      
    }
  } else {
    printf("%s not found.", fileName);
  }
  
  fclose(fp);
  return 0;
}
