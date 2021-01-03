#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const int PORT = 9999;
const int MAX_BUFFER = 300;

void processCommand(char[MAX_BUFFER], int, char*[]);

//  ./client 127.0.0.1 command
int main(int argc, char *argv[]) {

  char order[MAX_BUFFER];
  processCommand(order, argc, argv);
  printf("%s \n", order);

  return 0;
}

void processCommand(char order[MAX_BUFFER], int argc, char *argv[]) {

  char *ptr;

  for(unsigned i=2; i<argc; i++) {
    strcat(order, argv[i]);
    if(i != argc-1) {
      strcat(order, " ");
    }
  }

  ptr = (char *) calloc(5, sizeof(char));

  free(ptr);
}