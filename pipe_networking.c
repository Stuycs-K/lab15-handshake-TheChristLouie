#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "pipe_networking.h"

#define READ 0
#define WRITE 1

//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup(){
  int from_client = mkfifo(WKP, 0666);
  if (from_client==-1) printf("%s\n", strerror(errno));
  from_client = open(WKP, O_RDONLY);
  if (from_client==-1) printf("%s\n", strerror(errno));
  remove(WKP);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client){
  int from_client = server_setup();
  char str[20];
  read(from_client, str, sizeof(str));
  printf("Private Pipe Received: %s\n", str);
  int fd = open(str, O_WRONLY);
  if (fd == -1) {
    printf("%s\n", strerror(errno));
    return -1;
  }
  srand(time(NULL));
  int r = rand();
  printf("Sending random number: %d\n", r);
  if (write(fd, &r, sizeof(r)) == -1) {
    printf("Write error: %s\n", strerror(errno));
    return -1;
  }
  printf("Random number sent.\n");
  int ack;
  if (read(from_client, &ack, sizeof(int)) == -1){
    printf("Read error: %s\n", strerror(errno));
    return -1;
  }
  printf("Final Ack received: %d\n", ack);
  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server){
  char str[20];
  sprintf(str, "/tmp/%d", getpid());
  if (mkfifo(str, 0666) == -1){
    printf("%s\n", strerror(errno));
    return -1;
  }
  *to_server = open(WKP, O_WRONLY);
  if (*to_server == -1){
    printf("Error opening WKP: %s\n", strerror(errno));
    return -1;
  }
  if (write(*to_server, str, strlen(str) + 1) == -1){
    printf("Write error: %s\n", strerror(errno));
    return -1;
  }
  int from_server = open(str, O_RDONLY);
  if (from_server == -1) {
    printf("Error opening private pipe: %s\n", strerror(errno));
    return -1;
  }
  remove(str);
  int synack;
  if (read(from_server, &synack, sizeof(synack)) == -1){
    printf("Read error: %s\n", strerror(errno));
    return -1;
  }
  printf("Received random number: %d\n", synack);
  int ack = synack + 1;
  if (write(*to_server, &ack, sizeof(int)) == -1){
    printf("Write error: %s\n", strerror(errno));
    return -1;
  }
  printf("Client finished.\n");
  return from_server;
}