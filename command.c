#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "directory.h"

// From Lab 11
void parse_args(char *line, char **arg_ary) {
  char *curr = line;
  char *buffer;
  int i = 0;
  while(curr != NULL) {
    buffer = strsep(&curr, " ");
    arg_ary[i] = buffer;
    i++;
  }
  arg_ary[i] = NULL;
}

int parseCommands(char *line) {
  while(line != NULL) {
    char * command;
    command = strsep(&line, ";");

    char * args[16];
    parse_args(command, args);

    pid_t p;
    p = fork();
    if (p < 0) {
      perror("fork failed");
      exit(1);
    }
    else if (p == 0) {
      if(notCD(args)) {
        execvp(args[0], args);
      } else {
        exit(0);
      }
    }

    int status = 0;
    wait(&status);
  }
  return errno;
}
