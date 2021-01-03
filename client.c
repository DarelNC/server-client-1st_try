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

void processCommand(char[MAX_BUFFER], int, char*[]);
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

          char order[MAX_BUFFER];
          processCommand(order, argc, argv);
          printf("%s \n", order);

        /*  bzero(buffer, MAX_BUFFER);
          strcpy(buffer, order);
          write(comms_chanel, buffer, strlen(buffer));

          bzero(buffer, MAX_BUFFER);
          read(comms_chanel, buffer, MAX_BUFFER-1);
          printf("%s \n", buffer);*/

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

void processCommand(char order[MAX_BUFFER], int argc, char *argv[]) {

  for(unsigned i=2; i<argc; i++) {
    strcat(order, argv[i]);
    if(i != argc-1) {
      strcat(order, " ");
    }
  }

}