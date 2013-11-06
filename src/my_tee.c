#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "lib/error_functions.h"

void tee_exec(const int append, const char* outfile);

int main(int argc, char** argv, char** env) {
  int opt;
  int append = 0;
  char* outfile;
  while ((opt = getopt(argc, argv, "a")) != -1) {
    switch (opt) {
    case 'a':
      append = 1;
      break;
    default:
      fprintf(stderr, "Usage: %s [-a] outfile\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  if ((append && argc <= 2) || argc <= 1) {
    fprintf(stderr, "Usage: %s [-a] outfile\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  outfile = argv[optind];
  printf("append = %d outfile = %s\n", append, outfile);

  tee_exec(append, outfile);
  exit(EXIT_SUCCESS);
}

void tee_exec(const int append, const char* outfile) {
  int flags;
  int fd;
  ssize_t ret;
#define BUFSIZE 4096
  char buf[BUFSIZE];
  flags = O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC;
  if (append) {
    flags |= O_APPEND;
  }
  fd = open(outfile, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd < 0) {
    errExitEN(errno, "cannot open file %s", outfile);
  }
  while((ret = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
    ret = write(STDOUT_FILENO, buf, ret);
    if (ret < 0) {
      close(fd);
      errExitEN(errno, "write failed to STDOUT");
    }
    ret = write(fd, buf, ret);
    if (ret < 0) {
      close(fd);
      errExitEN(errno, "write failed to file:%s", outfile);
    }
  }
  if (ret < 0) {
    close(fd);
    errExitEN(errno, "read failed");
  }
  close(fd);
}
