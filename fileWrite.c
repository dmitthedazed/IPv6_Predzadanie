/* ========================================================================== */
/*                                                                            */
/*   fileWrite.c                                                              */
/*   E1: Write a string to a file using only open(), write(), close()         */
/*   Usage: ./fileWrite <filename> <message>                                  */
/*                                                                            */
/* ========================================================================== */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <filename> <message>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  const char *message = argv[2];

  // Open file: create or truncate, readable/writable by owner+group
  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  ssize_t written = write(fd, message, strlen(message));
  if (written == -1) {
    perror("write");
    close(fd);
    return 1;
  }

  if (close(fd) == -1) {
    perror("close");
    return 1;
  }

  printf("Written \"%s\" to file \"%s\"\n", message, filename);
  return 0;
}
