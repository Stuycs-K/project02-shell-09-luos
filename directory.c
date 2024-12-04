#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int notCD(char **arg_ary) {
  if(strcmp(arg_ary[0], "cd")) {
    chdir(arg_ary[1]);


    return 1;
  }
  return 0;
}
