#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#ifndef NETWORKING_H
#define NETWORKING_H
#define WKP "/tmp/mario"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 100

#define SYN 0
#define SYN_ACK 1
#define ACK 2

int server_handshake(int *to_client);
int client_handshake(int *to_server);

//used by server handshake
int server_setup();


#endif
