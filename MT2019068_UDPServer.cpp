#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Please provide port number\n");
    exit(1);
  }
  int sockfd, newsockfd, portno;
  // buffer for read and write
  char buffer[255];
  // buffer for sorting char
  char sortbuffer[255];
  // sockaddr structure for server addr and client addr
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;
  // create UDP, IP datagram socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket()");
    exit(1);
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  // convert port into interger specified by user
  portno = atoi(argv[1]);
  // scoket struture value
  serv_addr.sin_family = AF_INET;          //  IP
  serv_addr.sin_addr.s_addr = INADDR_ANY;  // 127.0.0.1
  serv_addr.sin_port = htons(portno);      // host to short number
  // bind server addr to socfd discriptor
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("bind()");
    exit(1);
  }

  clilen = sizeof(cli_addr);

  printf("Type d when you want to close the connection...\n");
  while (1) {
    bzero(buffer, 255);
    bzero(sortbuffer, 255);
    // read sockfd discriptor into buffer
    int n =
        recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *)&cli_addr, &clilen);
    int p = 0;
    // copy buffer char into sortbuffer
    while (buffer[p]) {
      sortbuffer[p] = buffer[p];
      p++;
    }
    // sort char in ascending order
    sort(sortbuffer, sortbuffer + (p - 1));

    if (n < 0) {
      perror("recvfrom()");
      exit(1);
    }
    printf("client: %s", buffer);
    bzero(buffer, 255);
    // send char in ascending order to client
    n = sendto(sockfd, sortbuffer, strlen(sortbuffer), 0,
               (struct sockaddr *)&cli_addr, sizeof(cli_addr));
    if (n < 0) {
      perror("write()");
      exit(1);
    }
    // sort char in desending order
    sort(sortbuffer, sortbuffer + (p - 1), greater<int>());
    // send char in descending order to client
    n = sendto(sockfd, sortbuffer, strlen(sortbuffer), 0,
               (struct sockaddr *)&cli_addr, sizeof(cli_addr));

    if (n < 0) {
      perror("write()");
      exit(1);
    }
    // if the buffer contain d then it close file discriptor
    int i = strncmp("d", sortbuffer, 1);
    if (i == 0) {
      break;
    }
  }
  close(sockfd);
  return 0;
}
