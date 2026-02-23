/* ========================================================================== */
/*                                                                            */
/*   fileAppend.c                                                             */
/*   E2: Append string with random prefix to file using open/write/close      */
/*   Usage: ./fileAppend <filename> <message>                                 */
/*                                                                            */
/* ========================================================================== */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <filename> <message>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  const char *message = argv[2];

  // Open file: create if not exists, append, readable/writable by owner
  int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  // Generate pseudo-random prefix
  srand((unsigned int)time(NULL));
  int prefix = rand() % 100000;

  // Prepare output buffer: "<prefix>: <message>\n"
  char outBuf[1280];
  int len = snprintf(outBuf, sizeof(outBuf), "%05d: %s\n", prefix, message);
  if (len < 0) {
    fprintf(stderr, "snprintf error\n");
    close(fd);
    return 1;
  }

  ssize_t written = write(fd, outBuf, (size_t)len);
  if (written == -1) {
    perror("write");
    close(fd);
    return 1;
  }

  if (close(fd) == -1) {
    perror("close");
    return 1;
  }

  printf("Appended \"%s\" with prefix %05d to file \"%s\"\n", message, prefix,
         filename);
  return 0;
}
