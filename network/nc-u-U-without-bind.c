/* This program works as a simplified "nc -u -U socket-file".
 * However, unlike nc, this program doesn't bind an address
 * to the socket created in this program. So, the server
 * cannot connect the server side socket to this client.
 *
 * By default, autobind doesn't work. With defining AUTOBIND,
 * kernel binds an abstract address to the client socket.
 * See "Autobind feature" secion in unix(7).
 */

//#define AUTOBIND 1

#include <sys/socket.h>
#include <sys/un.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
  if (argc < 2)
    errx(1, "Too few arugments: pass a socket file name as an argument");
  if (argc > 2)
    errx(1, "Too many arugments");

  fprintf(stderr, "pid: %d\n", getpid());
  
  int sd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sd < 0)
    err (1, "socket");

#ifdef AUTOBIND
  if (setsockopt(sd, SOL_SOCKET, SO_PASSCRED, &(int){1}, sizeof(int)) < 0)
    err (1, "setsockopt");
#endif  
  
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, argv[1]);
  
  if (connect(sd, (const struct sockaddr *)&addr, sizeof(addr)) < 0)
    err (1, "connect");

  // getchar ();
  
  if (write(sd, "a\n", 2) != 2)
    err(1, "write");

  char c[2];
  if (read(sd, c, 2) != 2)
    err(1, "read");
  
  return 0;
}
