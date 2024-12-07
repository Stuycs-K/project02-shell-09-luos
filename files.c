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
  int fd = -1;
  if (redir == 0) {
    fd = open(path, O_RDONLY);
  }
  else if (redir == 1) {
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0650);
  }
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

int checkRedirect(char *buffer, char **arg_ary, int i) {
  if (strcmp(buffer, "<") == 0) {
    arg_ary[i] = NULL;
    return 0;
  }
  else if (strcmp(buffer, ">") == 0) {
    arg_ary[i] = NULL;
    return 1;
  }
  return -1;
}
