#include "pipe_networking.h"
#include <stdio.h>
#include <string.h>

int main() {
  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  /* DO NOT EDIT ABOVE THIS */

  /*AFTER THIS LINE:
    Try to read/write from: from_client/to_client
    The order should correspond to your basic_client.
  */
  char *msg = "Hello Client\n";
  if (write(to_client, msg, strlen(msg) + 1) == -1){
    printf("Error in write: %s\n", strerror(errno));
    return 1;
  }
  printf("Message sent to client: %s\n", msg);

  sleep(5);

  char received[100];
  int err = read(from_client, received, sizeof(received));
  if (err == -1) {
    printf("Error in read: %s\n", strerror(errno));
    return 1;
  }
  printf("Server received: %s\n", received);

  return 0;
}