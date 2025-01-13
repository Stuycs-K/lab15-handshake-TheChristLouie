#include "pipe_networking.h"
#include <stdio.h>
#include <string.h>

int main() {
  int to_server;
  int from_server;
  from_server = client_handshake( &to_server );

  /* DO NOT EDIT ABOVE THIS */

  /*AFTER THIS LINE:
    Try to read/write from: from_server/to_server
    The order should correspond to your basic_server.
  */

  char received[100];
  int err = read(from_server, received, sizeof(received));
  if (err == -1){
    printf("Error in read: %s\n", strerror(errno));
    return 1;
  }
  received[err] = '\0';
  printf("Client received: %s\n", received);

  char *str = "Hello Server\n";
  if (write(to_server, str, strlen(str) + 1) == -1){
    printf("Error in write: %s\n", strerror(errno));
    return 1;
  }
  printf("Message sent to server: %s\n", str);

  return 0;
}
