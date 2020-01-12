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
  char buffer[255];      // create buffer for read and write
  char sortbuffer[255];  // create buffer for sorting a message
  // server addr and client addr
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;
  // socket call for ip datagram and tcp stream
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket()");
    exit(1);
  }
  // initial serv_addr set tom zero
  bzero((char *)&serv_addr, sizeof(serv_addr));
  // convert port number into integer
  portno = atoi(argv[1]);
  // set values to socket structure
  serv_addr.sin_family = AF_INET;          // ip
  serv_addr.sin_addr.s_addr = INADDR_ANY;  // 127.0.0.1
  serv_addr.sin_port = htons(portno);      // host to number short type
  // bind server addr to specified port number
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("bind()");
    exit(1);
  }
  // listen system call and backlog value is 5 that mean 5 server can listen to
  // 5 client symuntaneously
  listen(sockfd, 5);
  // 32 bit client addr
  clilen = sizeof(cli_addr);
  // create replica of sockfd and client coummunicate through newsockfd
  // discriptor
  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

  if (newsockfd < 0) {
    perror("accept()");
    exit(1);
  }
  printf("Type d when you want to close the connection...\n");
  while (1) {
    bzero(buffer, 255);
    bzero(sortbuffer, 255);
    // read newsockfd discriptor into buffer
    int n = read(newsockfd, buffer, 255);
    int p = 0;
    // copy buffer char into softbuffer
    while (buffer[p]) {
      sortbuffer[p] = buffer[p];
      p++;
    }
    // sort the char
    sort(sortbuffer, sortbuffer + (p - 1));
    if (n < 0) {
      perror("read()");
      exit(1);
    }
    printf("client: %s", buffer);
    bzero(buffer, 255);
    // send char to client in ascending  order
    n = write(newsockfd, sortbuffer, strlen(sortbuffer));
    if (n < 0) {
      perror("write()");
      exit(1);
    }
    sort(sortbuffer, sortbuffer + (p - 1), greater<int>());
    // send char to client in descending order
    n = write(newsockfd, sortbuffer, strlen(sortbuffer));
    if (n < 0) {
      perror("write()");
      exit(1);
    }
    // if the char is d then it close the discriptor
    int i = strncmp("d", sortbuffer, 1);
    if (i == 0) {
      break;
    }
  }
  close(newsockfd);
  close(sockfd);
  return 0;
}
