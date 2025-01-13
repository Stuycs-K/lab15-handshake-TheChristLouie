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
  
  int rec = 0;
  read(from_client, &rec, sizeof(int));
  printf("Received %d from client\n", rec);
  return 0;
}