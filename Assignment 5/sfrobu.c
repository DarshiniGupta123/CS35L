#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>

/*int readingError()
{
  if(ferror(stdin))
  {
    fprintf(stderr, "There was an error reading the file");
    return 1;
  }
  return 0;
  }
*/
int flag = 0;

int readingError()
{
  struct stat buf;
  ssize_t ret = fstat(STDIN_FILENO, &buf);
  if(ret == -1){
    char* message = "Input/Output Error\n" ;
    write(STDOUT_FILENO, message, 19);
    return 1;
  }
  else 
    return 0;
}

int memError(void *mem)
{
  if(mem == NULL)
  {
    free(mem);
    char* message = "Error in allocating memory\n";
    write(STDOUT_FILENO, &message, 27);
    return 1;
  }
  return 0;
}

char ignoreCase(char a)
{
  char b = a^42;
  return toupper((unsigned char) b);
}

int frobcmp(char const* x, char const* y){
  if(flag){
    for(;; x++, y++){
      if(*x == ' ' && *y == ' ')
	return 0;
      else if ((*x == ' ') || ignoreCase(*x) < ignoreCase(*y))
	return -1;
      else if ((*y == ' ') || ignoreCase(*y) < ignoreCase(*x))
	return 1;
    }
  }
  else{
    for(;; x++, y++){
      if(*x == ' ' && *y == ' ')
        return 0;
      else if ((*x == ' ') || (*x^42) < (*y^42))
        return -1;
      else if ((*y == ' ') || (*y^42) < (*x^42))
        return 1;
    }
  }
}


int cmp(const void* a, const void* b)
{
  return frobcmp(*(char**) a, *(char**) b);
}

int regFile(){
  struct stat buf;
  if(S_ISREG(buf.st_mode))
    return 1;
  else
    return 0;
}

int main(int argc, const char* argv[])
{
  int regular = 0;
  char* oneWord;
  ssize_t filesize;
 
  if(regFile()){
    struct stat buf;
    ssize_t ret = fstat(STDIN_FILENO, &buf);
    filesize = buf.st_size + 1;
    oneWord = (char*)malloc(sizeof(char) * filesize);
    regular = 1;
  }
  else
    oneWord = (char*)malloc(sizeof(char));

  char** dict = (char**)malloc(sizeof(char*));

  int count1 = 0;
  int count2 = 0;

  if(memError(oneWord) || memError(dict))
    exit(1);

  //char cur = getchar();
  char cur;
  ssize_t numRead = read(STDIN_FILENO, &cur, 1);
  if(readingError())
    exit(1);
  char next;
  ssize_t numRead2 = read(STDIN_FILENO, &next, 1);
  if(readingError())
    exit(1);
  //int isEOF = feof(stdin);
  while(numRead >= 1){
    oneWord[count1] = cur;
    if((count1 > (filesize - 1)) || (regular == 0))
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
      if(regular)
	oneWord = (char*)malloc(sizeof(char)*filesize);
      else
	oneWord = (char*)malloc(sizeof(char));
      count1 = 0;
    }
    //isEOF = feof(stdin);
    if(cur == ' ' && numRead2 == 0)
      break;
    else if(numRead2 == 0){
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
      numRead2 = read(STDIN_FILENO, &next, 1);
      if(readingError())
	exit(1);
    }
    else if(cur == ' ' && next == ' '){
      while(next == ' '){
	numRead2 = read(STDIN_FILENO, &next, 1);
        if(readingError())
          exit(1);
      }
      cur = next;
      numRead2 = read(STDIN_FILENO, &next, 1);
      count1++;
      if(readingError())
        exit(1);
    }

    else{
      cur = next;
      numRead2 = read(STDIN_FILENO, &next, 1);
      if(readingError())
	exit(1);
    }
  }

  if(argc == 2)
  {
    if(!(strncmp(argv[1], "-f", 2)))
      flag = 1;    
  }

  qsort(dict, count2, sizeof(char*), cmp);

  int a;
  int b;
  for(a = 0; a < count2; a++){
    for(b = 0; dict[a][b] != ' '; b++){
      char lett = dict[a][b];
      write(STDOUT_FILENO, &lett, 1); 
    }
    char sp = ' ';
    write(STDOUT_FILENO, &sp, 1);
  }
  
  free(dict);
  exit(0);
}
