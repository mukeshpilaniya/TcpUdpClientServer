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
  // buffer for read and write
  char buffer[256];
  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }
  // convert port into integer
  portno = atoi(argv[2]);
  // create tcp stream socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket()");
    exit(1);
  }
  // get hostanme specified by user
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "error, no such host\n");
    exit(1);
  }

  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);  // host to number short
  // connect scoket file discriptor to server addr
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("connect()");
    exit(1);
  }

  printf("Type d when you want to close the connection...\n");
  while (1) {
    printf("Client: ");
    bzero(buffer, 256);
    // read stream of char using stdin
    fgets(buffer, 256, stdin);
    // send char to server
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
      perror("write()");
      exit(1);
    }
    printf("\n");
    bzero(buffer, 256);
    n = read(sockfd, buffer, 256);
    if (n < 0) {
      perror("read()");
    }
    // print char in ascending order
    printf("server: %s", buffer);
    int m = read(sockfd, buffer, 256);
    if (m < 0) {
      perror("read()");
    }
    // print char in decensing order
    printf("server: %s\n", buffer);
    // if the char is d then it close socket discriptor
    int i = strncmp("d", buffer, 1);
    if (i == 0) {
      break;
    }
  }
  close(sockfd);
  return 0;
}
