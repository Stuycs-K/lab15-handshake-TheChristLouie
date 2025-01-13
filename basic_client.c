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

  int number = 25;
  write(to_server,&number,sizeof(int));
  printf("Wrote %d\n", number);
  return 0;
}
