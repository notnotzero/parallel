#include <ctype.h>
#include <omp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i = 0;
  int answer = 0;

  
  
  for (i = 0; i < strlen(argv[1]); i++){
    if ((argv[1][i] == ' ') || (argv[1][i] == '\t')  || (argv[1][i] == '\n')){
      answer += 1;
    }
  }

  if (strlen(argv[1]) > 0){
    answer += 1;
  }

  printf("String %s contains %d words.\n", argv[1], answer);
}