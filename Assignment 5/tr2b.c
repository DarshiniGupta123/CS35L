#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]){
  if(argc != 3){
    fprintf(stderr, "Wrong number of arguments!\n");
    exit(1);
  }

  const char* from = argv[1];
  const char* to = argv[2];
  
  if(strlen(from) != strlen(to)){
    fprintf(stderr, "From and To are not the same length!\n");
    exit(1);
  }

  int i = 0;
  int k = 0;
  for(i = 0; i < strlen(from); i++){
    k = i + 1;
    for(; k < strlen(from); k++){
    if(from[i] == from[k]){
      fprintf(stderr, "Duplicates found, error!\n");
      exit(1);
    }
    }
  }
  int flag = 1;
  int letter = getchar();
  while(!feof(stdin)){
    int j = 0;
    for(j = 0; j < strlen(from); j++){
      if(letter == from[j]){
	flag = 0;
	putchar(to[j]);
	break;
      }
    }
   
    if(flag){
      putchar(letter);
    }
    flag = 1;
    letter = getchar();
  }
  exit(0);
}
