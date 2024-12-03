#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int notCD(char **arg_ary) {
  if(strcmp(arg_ary[0], "cd")) {
    chdir(arg_ary[1]);

    char buffer[100];
    printf("%s\n", getcwd(buffer, 100));
    return 1;
  }
  return 0;
}
