#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define DEBUG

int main(int argc, char** argv) {
  char* filename;
  long num_bytes;
  int x_mode = 0;
  if (argc == 4) {
    x_mode = 1;
  }
  if (!(argc == 3 || argc == 4)) {
    usageErr("Usage: %s filename num_bytes [x]\n", argv[0]);
  }
  filename = argv[1];
  num_bytes = atoi(argv[2]);
#ifdef DEBUG
  printf("filename: %s num_bytes: %ld\n", filename, num_bytes);
#endif
  /* phase 1 */
  int fd;
  int flags = O_CREAT | O_RDWR;
  int ret;
  if (!x_mode) {
    flags |= O_APPEND;
  }
  fd = open(filename, flags, 0644);
  if (fd == -1) {
    errExit("open");
  }
  long i;
  for (i = 0 ; i < num_bytes; i++) {
    if (x_mode) {
      ret = lseek(fd, 0, SEEK_END);
      if (ret == -1) {
        errExit("lseek");
      }
      ret = write(fd, "x", 1);
      if (ret == -1) {
        errExit("write");
      }
    } else {
      ret = write(fd, "x", 1);
      if (ret == -1) {
        errExit("write");
      }
    }
  }
  close(fd);
}
