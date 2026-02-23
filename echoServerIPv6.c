/* ========================================================================== */
/*                                                                            */
/*   echoServerIPv6.c                                                         */
/*   TCP/IPv6 echo server - receives message, replies with uppercase version  */
/*   Usage: ./serverIPv6 <server_ipv6>                                        */
/*   Port: 5000 (fixed)                                                       */
/*                                                                            */
/* ========================================================================== */
#include "settings.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 5000

char Buff[MAX_MSG_SIZE];

int server_sockfd = -1;
int client_sockfd = -1;

void cleanup(void) {
  if (server_sockfd != -1) {
    close(server_sockfd);
    server_sockfd = -1;
  }
  if (client_sockfd != -1) {
    close(client_sockfd);
    client_sockfd = -1;
  }
}

int strToUpper(char *str, int size) {
  int i = 0;
  while (*str != '\0' && i++ < size) {
    *str = toupper(*str);
    str++;
  }
  return i;
}

int main(int argc, const char *argv[]) {

  struct sockaddr_in6 server_address;
  struct sockaddr_in6 client_address;
  socklen_t client_len;
  int opt = 1;

  if (argc < 2) {
    printf("server error: no IPv6 address specified.\n");
    return 1;
  }
  atexit(cleanup);

  // Create TCP/IPv6 socket
  _runSafe(server_sockfd = socket(AF_INET6, SOCK_STREAM, 0));

  // Allow address reuse
  setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // Bind to specified IPv6 address and fixed port
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin6_family = AF_INET6;
  server_address.sin6_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET6, argv[1], &server_address.sin6_addr) != 1) {
    fprintf(stderr, "Invalid IPv6 address: %s\n", argv[1]);
    return 1;
  }
  _runSafe(bind(server_sockfd, (struct sockaddr *)&server_address,
                sizeof(server_address)));

  // Start listening
  _runSafe(listen(server_sockfd, 5));

  while (1) {

    printf("Server waiting.\n");

    // Accept incoming connection
    client_len = sizeof(client_address);
    _runSafe(client_sockfd =
                 accept(server_sockfd, (struct sockaddr *)&client_address,
                        &client_len));

    // Read message from client
    _runSafe(read(client_sockfd, Buff, MAX_MSG_SIZE));
    printf("Server received: %s\n", Buff);

    // Convert to uppercase and send reply
    strToUpper(Buff, MAX_MSG_SIZE);
    _runSafe(write(client_sockfd, Buff, strlen(Buff) + 1));

    // Close client socket
    close(client_sockfd);
    client_sockfd = -1;
  }

  return 0;
}
