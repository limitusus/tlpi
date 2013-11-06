#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fs.h>
#include "tlpi_hdr.h"

int is_all_nul(const char* buf, const size_t bufsize) {
  size_t i;
  for (i = 0; i < bufsize; i++) {
    if (buf[i]) {
      return 0;
    }
  }
  return 1;
}

void copyfile(const char* from_fname, const char* to_fname) {
  int in_fd, out_fd;
  ssize_t ret;
  in_fd = open(from_fname, O_RDONLY);
  if (in_fd == -1) {
    errExit("open");
  }
  out_fd = open(to_fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (out_fd == -1) {
    errExit("open");
  }
  /* copy */
#define BUFSIZE 1024
  char buf[BUFSIZE];
  while ((ret = read(in_fd, buf, BUFSIZE)) > 0) {
    if (is_all_nul(buf, BUFSIZE)) {
      lseek(out_fd, BUFSIZE, SEEK_CUR);
    } else {
      ret = write(out_fd, buf, ret);
      if (ret == -1) {
        errExit("write");
      }
    }
  }
  if (ret == -1) {
    errExit("read");
  }
  close(out_fd);
  close(in_fd);
}

int main(int argc, char** argv) {
  int opt;
  char* from_fname, *to_fname;
  /*
  while ((opt = getopt(argc, argv, "")) != -1) {
    switch (opt) {
    case 'a':
      append = 1;
      break;
    default:
      fprintf(stderr, "Usage: %s [-a] outfile\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  */
  if (argc != 3) {
    usageErr("Usage: %s FROM TO\n", argv[0]);
  }
  from_fname = argv[1];
  to_fname = argv[2];
  copyfile(from_fname, to_fname);
}
