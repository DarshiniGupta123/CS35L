#include <stdio.h>
#include <stdlib.h>

int readingError()
{
  if(ferror(stdin))
  {
    fprintf(stderr, "There was an error reading the file");
    return 1;
  }
  return 0;
}

int memError(void *mem)
{
  if(mem == NULL)
  {
    free(mem);
    fprintf(stderr, "There was an error in allocating memory");
    return 1;
  }
  return 0;
}

int frobcmp(char const* x, char const* y){
  for(;; x++, y++){
    if(*x == ' ' && *y == ' ')
	return 0;
    else if ((*x == ' ') || (*x ^ 42) < (*y ^ 42))
	return -1;
    else if ((*y == ' ') || (*y ^ 42) < (*x ^42))
	return 1;
  }
}

int cmp(const void* a, const void* b)
{
  return frobcmp(*(char**) a, *(char**) b);
}

int main(void)
{
  char* oneWord = (char*)malloc(sizeof(char));
  char** dict = (char**)malloc(sizeof(char*));

  int count1 = 0;
  int count2 = 0;

  if(memError(oneWord) || memError(dict))
    exit(1);

  char cur = getchar();
  if(readingError())
    exit(1);
  char next = getchar();
  if(readingError())
    exit(1);
  int isEOF = feof(stdin);
  while(!isEOF){
    oneWord[count1] = cur;
    oneWord = (char*)realloc(oneWord, (count1 + 2)*sizeof(char));
    count1++;
    if(memError(oneWord))
      exit(1);
    if(cur == ' '){
      dict[count2] = oneWord;
      dict = (char**)realloc(dict, (count2 + 2)*sizeof(char*));
      if(memError(dict))
	exit(1);
      count2++;
      oneWord = NULL;
      oneWord = (char*)malloc(sizeof(char));
      count1 = 0;
    }
    isEOF = feof(stdin);
    if(cur == ' ' && isEOF)
      break;
    else if(isEOF){
      cur = ' ';
      oneWord[count1] = cur;
      dict[count2] = oneWord;
      dict = (char**)realloc(dict, (count2 + 2)*sizeof(char*));
      if(memError(dict))
	exit(1);
      count2++;
      break;
    }  

    else if(cur == ' ' && next != ' '){
      cur = next;
      next = getchar();
      if(readingError())
	exit(1);
    }
    else if(cur == ' ' && next == ' '){
      while(next == ' '){
        next = getchar();
        if(readingError())
          exit(1);
      }
      cur = next;
      next = getchar();
      count1++;
      if(readingError())
        exit(1);
    }

    else{
      cur = next;
      next = getchar();
      if(readingError())
	exit(1);
    }
  }
   

  qsort(dict, count2, sizeof(char*), cmp);

  int a;
  int b;
  for(a = 0; a < count2; a++){
    for(b = 0; dict[a][b] != ' '; b++){
      putchar(dict[a][b]);
    }
    //printf("%d: %s\n", a, dict[a]);
    putchar(' ');
  }
  
  free(dict);
  exit(0);
}
