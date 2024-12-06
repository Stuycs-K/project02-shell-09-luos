#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "files.h"

int* parse_args(char *line, char **arg_ary) {
  char *curr = line;
  char *buffer;
  int i = 0;
  int redir = -1;
  while(curr != NULL) {
    buffer = strsep(&curr, " ");

    if(redir != -1) {
      int* descrs = redirect(buffer, redir);
      return descrs;
    }

    if (strcmp(buffer, "<") == 0) {
      arg_ary[i] = NULL;
      redir = 0;
    }
    else if (strcmp(buffer, ">") == 0) {
      arg_ary[i] = NULL;
      redir = 1;
    }

    if(redir == -1) {
      arg_ary[i] = buffer;
    }
    i++;
  }
  arg_ary[i] = NULL;
  return NULL;
}

int parseCommands(char *line) {
  while(line != NULL) {
    char * command;
    command = strsep(&line, ";");

    char * args[16];
    int* descrs = parse_args(command, args);

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

    if(descrs != NULL) {
      dup2(descrs[1], descrs[0]);
      free(descrs);
    }
  }
  return errno;
}
