#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const int PORT = 9999;
const int MAX_BUFFER = 300;
const char NUL = '\0';
const char SPACE = ' ';


void processCommand(int, char*[]);

//  ./client 127.0.0.1 command
int main(int argc, char *argv[]) {

  char order[MAX_BUFFER];
  processCommand(argc, argv);
  //printf("%s \n", order);

  return 0;
}
//  ./code 127.0.0.1 command1 command2
void processCommand(int argc, char *argv[]) {
  int index = 0;
  //char NUL = '\0';
  //char SPACE = ' ';
  int order_size = 0;

  
  for(unsigned i=2; i<argc; i++) {
    order_size += strlen(argv[i]);
  }

  char order[order_size];

  for(unsigned i=2; i<argc; i++) {
    for(unsigned j=0; j<strlen(argv[i]); j++, index++) {
      order[index] = argv[i][j];
    }
    order[index] = SPACE;
    index++;
  }
  order[index-1] = NUL;

  printf("%s \n", order);


  //return order;
}


/*
void processCommand(char order[MAX_BUFFER], int argc, char *argv[]) {

  for(unsigned i=2; i<argc; i++) {
    strcat(order, argv[i]);
    if(i != argc-1) {
      strcat(order, " ");
    }
  }

}
*/
