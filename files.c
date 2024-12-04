#include <errno.h>
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
