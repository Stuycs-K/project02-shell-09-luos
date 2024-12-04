#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int notCD(char **arg_ary) {
  if(strcmp(arg_ary[0], "cd") == 0) {
    int number = chdir(arg_ary[1]);
    if(number < 0) {
        perror("cd failed\n");
        exit(-1);
    }
    return 1;
  }
  return 0;
}

int redirect(char *path, int inOut) {
  int fd = open(path, O_WRONLY);
  int fileno = inOut;
  int backup = dup(fileno);
  dup2(fd, fileno);
  return backup;
}

int checkRedirect(char **arg_ary, int size) {
  for (int i = 0; i < size-1; i++) {
    if(strcmp(arg_ary[i], ">") == 0) {
      return redirect(arg_ary[i+1], 1);
    }
    else if(strcmp(arg_ary[i], "<") == 0) {
      return redirect(arg_ary[i+1], 0);
    }
  }
  return 0;
}
