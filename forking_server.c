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
Make a new file for this part: forking_server.c (copy your working persistant_server.c and start with that.) This server fork to handle multiple concurrent connections.

The server should only:

    create the WKP
    await a connection
    upon connection remove the WKP.
    Fork to create a subserver which will handle the client.
    Go back to step 1.

*/

int main() {
  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  while
}
