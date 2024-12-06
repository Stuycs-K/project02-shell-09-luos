#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void changeDir(char **args) {
  int number = chdir(args[1]);
  if(number < 0) {
      perror("cd failed\n");
      exit(-1);
  }
}

int* redirect(char *path, int redir) {
  int fd = open(path, O_WRONLY | O_CREAT, 0650);
  if (fd < 0) {
    perror("failed file open\n");
    exit(-1);
  }
  int out = redir;
  int backup = dup(out);
  dup2(fd, out);

  int* descrs = malloc(2*sizeof(int));
  descrs[0] = out;
  descrs[1] = backup;
  return descrs;
}
