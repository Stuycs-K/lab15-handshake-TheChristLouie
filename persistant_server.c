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

#include "pipe_networking.h"

/*
Make a new file for this part: persistant_server.c™ (copy your working basic_server.c and start with that).

    Have the server loop to accept a new clients after the first client disconnects (ctrl-c the client). That is many sequential clients, one after another.
    Close the old file descriptors before you end your loop, or you will have an ever-growing file table. (close from_client and to_client)
    You must now also add a sighandler for SIGINT. This will delete the WKP befor ending the server.

*/

int main() {
  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  while
}
