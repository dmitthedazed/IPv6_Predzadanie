/* ========================================================================== */
/*                                                                            */
/*   echoClientIPv6.c                                                         */
/*   TCP/IPv6 echo client - sends message to server, receives uppercase reply */
/*   Usage: ./clientIPv6 <server_ipv6>                                        */
/*   Port: 5000 (fixed)                                                       */
/*                                                                            */
/* ========================================================================== */
#include "settings.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 5000

char Buff[MAX_MSG_SIZE]; // output message buffer
char Fubb[MAX_MSG_SIZE]; // input message buffer

int Sock_fd = -1;

void cleanup(void) {
  if (Sock_fd != -1) {
    close(Sock_fd);
    Sock_fd = -1;
  }
}

int main(int argc, const char *argv[]) {

  struct sockaddr_in6 address;

  if (argc < 2) {
    printf("client error: no IPv6 address specified.\n");
    return 1;
  }
  atexit(cleanup);

  // Prepare message (lowercase string)
  snprintf(Buff, MAX_MSG_SIZE, "hello from client (ipv6)");

  // Create TCP/IPv6 socket
  _runSafe(Sock_fd = socket(AF_INET6, SOCK_STREAM, 0));

  // Set server address
  memset(&address, 0, sizeof(address));
  address.sin6_family = AF_INET6;
  address.sin6_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET6, argv[1], &address.sin6_addr) != 1) {
    fprintf(stderr, "Invalid IPv6 address: %s\n", argv[1]);
    return 1;
  }

  // Connect to server
  _runSafe(connect(Sock_fd, (struct sockaddr *)&address, sizeof(address)));

  printf("client sending message:%s\n", Buff);
  // Write message to socket
  _runSafe(write(Sock_fd, Buff, strlen(Buff) + 1));

  // Read reply from server
  _runSafe(read(Sock_fd, Fubb, MAX_MSG_SIZE));

  printf("client received reply from server:%s\n", Fubb);

  // Close connection
  close(Sock_fd);
  Sock_fd = -1;

  return 0;
}
