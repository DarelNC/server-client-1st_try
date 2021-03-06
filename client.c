#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

const int PORT = 9999;
const int MAX_BUFFER = 300;
const char SPACE = ' ';
const char NUL = '\0';

void processCommand(int, char*[]);
void error(const char *);

//  ./client 127.0.0.1 command
int main(int argc, char *argv[]) {
  int comms_chanel, server;
  struct sockaddr_in server_address;
  char buffer[MAX_BUFFER];

  if(argc < 3) {
    error("Not enough arguments. \n");
  }
  else {
    comms_chanel = socket(AF_INET, SOCK_STREAM, 0);
    if(comms_chanel < 0) {
      error("Error opening socket. \n");
    }
    else {
      printf("Socket established. \n");

      server = inet_addr(argv[1]);
      if(server == -1) {
        error("Error, no such host. \n");
      }
      else {
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);
        server_address.sin_addr.s_addr = inet_addr(argv[1]);

        //Connect()
        if(connect(comms_chanel, (struct sockaddr *) &server_address, 
            sizeof(server_address)) < 0) {
          error("Error connecting. \n");
        }
        else {
          printf("Established connection. \n");

          
          
          /*--------------Method >>processCommand<< goes here---------------*/
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
          




          bzero(buffer, MAX_BUFFER);
          strcpy(buffer, order);
          write(comms_chanel, buffer, strlen(buffer));

          bzero(buffer, MAX_BUFFER);
          read(comms_chanel, buffer, MAX_BUFFER-1);
          printf("%s \n", buffer);

        }
      }
      close(comms_chanel);
    }
  }

  return 0;
}

void error(const char *msg) {
  perror(msg);
  exit(0);
}

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