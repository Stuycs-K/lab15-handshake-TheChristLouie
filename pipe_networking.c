#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "pipe_networking.h"

#define READ 0
#define WRITE 1

//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client;
  mkfifo("well_known_pipe",0666);
  from_client = open("well_known_pipe", O_RDONLY);
  remove("well_known_pipe");
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  from_client = server_setup()
  int fd = open("well_known_pipe", O_WRONLY);
  write(sprintf("%d",getpid()));
  mkfifo(sprintf("%d",getpid()),0666);
  *to_client = open(sprintf("%d",getpid()),O_RDONLY);
  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  from_server= open("well_known_pipe",O_RDONLY);
  *to_server = open(sprintf("%d",getpid()),O_WRONLY);
  return from_server;
}
