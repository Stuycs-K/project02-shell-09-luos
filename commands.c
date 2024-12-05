#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "files.h"

void parse_args(char *line, char **arg_ary) {
  char *curr = line;
  char *buffer;
  int i = 0;
  while(curr != NULL) {
    buffer = strsep(&curr, " ");
    if(strcmp(buffer, "<") == 0) {
      arg_ary[i] = NULL;
      // redirect(arg_ary[i+1]
    }
    arg_ary[i] = buffer;
    i++;
  }
  arg_ary[i] = NULL;
}

void changeDir(char **args) {
  int number = chdir(args[1]);
  if(number < 0) {
      perror("cd failed\n");
      exit(-1);
  }
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
      if(strcmp(args[0], "cd") == 0) {
        changeDir(args);
      }
      else {
        execvp(args[0], args);
      }
    }

    int status = 0;
    wait(&status);
  }
  return errno;
}
