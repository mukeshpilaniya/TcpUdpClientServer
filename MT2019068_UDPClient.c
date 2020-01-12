#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, int *argv[]) {
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }
  // convert port number into interger
  portno = atoi(argv[2]);
  // create UDP,IP socket for communication
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket()");
    exit(1);
  }
  // get hostname specified by user (127.0.0.1)
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "error, no such host\n");
    exit(1);
  }

  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;  // IP datagram
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);  // host to short number

  printf("Type d when you want to close the connection...\n");
  while (1) {
    printf("Client: ");
    bzero(buffer, 256);
    // get stream of char using stdin
    fgets(buffer, 256, stdin);
    // send buffer value to server
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr,
               sizeof(serv_addr));
    if (n < 0) {
      perror("write()");
      exit(1);
    }
    bzero(buffer, 256);
    // read sockfd discriptor vulue into buffer
    n = recvfrom(sockfd, buffer, 256, 0, NULL, NULL);
    if (n < 0) {
      perror("read()");
    }
    printf("\n");
    // print number in ascending order
    printf("server: %s", buffer);
    n = recvfrom(sockfd, buffer, 256, 0, NULL, NULL);
    if (n < 0) {
      perror("read()");
    }
    // print number in descending order
    printf("server: %s\n", buffer);
    // if buffer contain d then it close sockfd discriptor
    int i = strncmp("d", buffer, 1);
    if (i == 0) {
      break;
    }
  }
  close(sockfd);
  return 0;
}
