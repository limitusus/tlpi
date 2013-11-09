#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "tlpi_hdr.h"


#define TGTFILE "/tmp/tgt.txt"

int main(int argc, char** argv) {
  int fd;
  int ret;
  /* init */
  fd = open(TGTFILE, O_CREAT | O_TRUNC | O_CLOEXEC | O_WRONLY, 0644);
  if (fd == -1) {
    errExit("open");
  }
  ret = write(fd, "EXISTING_DATA", 14);
  if (ret == -1) {
    errExit("write");
  }
  close(fd);
  fd = open(TGTFILE, O_APPEND | O_RDWR);
  if (fd == -1) {
    errExit("open");
  }
  lseek(fd, 0, SEEK_SET);
  ret = write(fd, "appended_data", 14);
  if (ret == -1) {
    errExit("write");
  }
  close(fd);
}
