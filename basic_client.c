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

  int rec = 0;
  read(from_server, &rec, sizeof(int));
  printf("%d\n",rec);
  close(to_server);
  close(from_server);
  return 0;
}
