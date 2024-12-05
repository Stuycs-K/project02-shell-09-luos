#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINE_SIZE 16

int redirect(char *path, int inOut) {
  int fd = open(path, O_WRONLY);
  int fileno = inOut;
  int backup = dup(fileno);
  dup2(fd, fileno);
  return backup;
}

int checkRedirect(char **arg_ary, int size) {
  for (int i = 0; i < size-1; i++) {
    if(arg_ary[i] == NULL) {
      return 0;
    }
    if(strcmp(arg_ary[i], ">") == 0) {
      return redirect(arg_ary[i+1], 1);
    }
    else if(strcmp(arg_ary[i], "<") == 0) {
      return redirect(arg_ary[i+1], 0);
    }
  }
  return 0;
}
