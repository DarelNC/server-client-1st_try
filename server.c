#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

const int PORT          = 9999;
const int TOTAL_REQUEST = 3;
const int MAX_BUFFER    = 300;

void error(const char *msg) {
  perror(msg);
  exit(1);
}

int main() {
  int comms_chanel, network_socket;
  struct sockaddr_in server_address, client_address;
  socklen_t client_lenght;
  char buffer[MAX_BUFFER];


  /*Lets start!!*/
  comms_chanel = socket(AF_INET, SOCK_STREAM, 0);
  if(comms_chanel < 0) {
    error("Error opening socket. \n");
  }
  else {
    printf("Socket established. \n");

    /*Assign values to --server_address--*/
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port        = htons(PORT);

    /*Binding*/
    if(bind(comms_chanel, (struct sockaddr *) &server_address, 
      sizeof(server_address)) < 0) {
        error("Error on binding. \n");
    }
    else {
      printf("Bind correct. \n");

      /*Listen*/
      listen(comms_chanel, TOTAL_REQUEST);
      printf("Listen correct. \n");

      while(1) {
        /*ACCEPT*/
        client_lenght = sizeof(client_address);
        network_socket = accept(comms_chanel, (struct sockaddr *) &client_address, 
                                &client_lenght);
        if(network_socket < 0) {
          error("Error on accept. \n");
        }
        else {
          printf("Accepted");

          int tuberia[2];
          if(pipe(tuberia) == -1) {
            error("Error creating pipe. \n");
          }

          int pid = fork();
          if(pid == 0) {
            int std_in = dup(0);
            int std_out = dup(1);

            close(0); //Read
            close(1); //Write
            dup(tuberia[0]);
            dup(tuberia[1]);

            bzero(buffer, MAX_BUFFER);
            read(network_socket, buffer, MAX_BUFFER-1);
            system(buffer);

            bzero(buffer, MAX_BUFFER);
            read(tuberia[0], buffer, MAX_BUFFER-1);
            write(network_socket, buffer, strlen(buffer));

            close(tuberia[0]);
            close(tuberia[1]);

            close(0);
            close(1);
            dup(std_in);
            dup(std_out);
            close(std_in);
            close(std_out);

            close(network_socket);
          }
          else {
            wait(NULL);
            
            close(tuberia[0]);
            close(tuberia[1]);

            exit(0);
          }
        }
      } //while
    }
    close(comms_chanel);
  }

  return 0;
}