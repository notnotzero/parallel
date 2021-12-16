#include <ctype.h>
#include <omp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i = 0;
  int answer = 0;

  bool flag = false;
  
  for (i = 0; i < strlen(argv[1]); i++){
    if (((argv[1][i] == ' ') || (argv[1][i] == '\t')  || (argv[1][i] == '\n')) && flag == true){
      flag = false;
    }

    if (!((argv[1][i] == ' ') || (argv[1][i] == '\t')  || (argv[1][i] == '\n')) && flag == false){
      answer += 1;
      flag = true;
    }    

  }

  printf("String %s contains %d words.\n", argv[1], answer);
}