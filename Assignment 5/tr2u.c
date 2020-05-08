#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, const char* argv[]){
  if(argc != 3){
    //fprintf(stderr, "Wrong number of arguments!\n");
    char* message = "Wrong number of arguments!\n";
    write(STDOUT_FILENO, message, 28);
    exit(1);
  }

  const char* from = argv[1];
  const char* to = argv[2];

  if(strlen(from) != strlen(to)){
    //fprintf(stderr, "From and To are not the same length!\n");
    char message[] = "From and To are not the same length!\n";
    write(STDOUT_FILENO, &message, 37);
    exit(1);
  }

  int i = 0;
  int k = 0;
  for(i = 0; i < strlen(from); i++){
    k = i + 1;
    for(; k < strlen(from); k++){
    if(from[i] == from[k]){
      //fprintf(stderr, "Duplicates found, error!\n");
      char* message = "Duplicates found, error!\n";
      write(STDOUT_FILENO, message, 25);
      exit(1);
    }
    }
  }
  int flag = 1;
  char letter;
  int numRead = read(STDIN_FILENO, &letter, 1);
  while(numRead >= 1){
    int j = 0;
    for(j = 0; j < strlen(from); j++){
      if(letter == from[j]){
        flag = 0;
	letter = to[j];
        write(STDOUT_FILENO, &letter, 1);
        break;
      }
    }

    if(flag){
      write(STDOUT_FILENO, &letter, 1);
    }
    flag = 1;
    numRead = read(STDIN_FILENO, &letter, 1);
  }
  exit(1);
}
