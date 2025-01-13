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

int main(){
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);
  int to_client;
  int from_client;
  while(1) {
    from_client = server_handshake( &to_client );
    pid_t p = fork();
    if(p < 0){
      printf("Fork error %s\n", strerror(errno));
      exit(1);
    }
    if(p == 0){
      while(1){
        int received;
        sleep(1);
        if(read(from_client, &received,sizeof(int))<=0){
          printf("Client Exited\n");
          break;
        }
        printf("%d Recieved %d\n", getpid(), received);
      }
      close(to_client);
      close(from_client);
      exit(1);
    }
    else{
      close(to_client);
      close(from_client);
    }
  }
  return 0;
}

static void sighandler(int signo){
  if(signo == SIGINT){
    remove(WKP);
    exit(1);
  }
}