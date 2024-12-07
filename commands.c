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
    redir = checkRedirect(buffer, arg_ary, i);

    if(redir == -1) {
      arg_ary[i] = buffer;
    }
    i++;
  }
  arg_ary[i] = NULL;
  return NULL;
}

void exec(char **args) {
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

int parseCommands(char *line) {
  while(line != NULL) {
    char * secondCommand;
    secondCommand = strsep(&line, ";");

    char * firstCommand;
    // https://stackoverflow.com/questions/12784766/check-substring-exists-in-a-string-in-c
    if(strstr(secondCommand, " | ") != NULL) {
      firstCommand = strsep(&secondCommand, " | ");
      secondCommand = secondCommand + 2;
    }
    else if(strstr(secondCommand, "|") != NULL) {
      firstCommand = strsep(&secondCommand, "|");
    }
    else {
      firstCommand = secondCommand;
      secondCommand = NULL;
    }

    int* pipeDescrs;
    if(secondCommand != NULL) {
      pipeDescrs = redirect("temp.txt", 1);
    }

    char * args[16];
    int* descrs = parse_args(firstCommand, args);
    exec(args);

    if(descrs != NULL) {
      dup2(descrs[1], descrs[0]);
      free(descrs);
    }
    if(secondCommand != NULL) {
      dup2(pipeDescrs[1], pipeDescrs[0]);
      free(pipeDescrs);
    }
    printf("HIT\n");
  }
  return errno;
}
