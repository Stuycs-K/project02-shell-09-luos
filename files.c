#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINE_SIZE 16

void changeDir(char **args) {
  int number = chdir(args[1]);
  if(number < 0) {
      perror("cd failed\n");
      exit(-1);
  }
}

int* redirect(char *path, int inOut) {
  int descriptors[2];
  descriptors[0] = open(path, O_WRONLY);
  int fileno = inOut;
  descriptors[1] = dup(fileno);
  dup2(descriptors[0], fileno);
  return descriptors;
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
