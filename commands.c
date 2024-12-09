#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "files.h"

/**
  Description:
    Parses a line containing a command, arguments, and redirects,
    placing the command + arguments into an array and automatically
    redirecting stdin/stdout.
  Parameters:
    char* line - A string containing the command + arguments + redirection mechanism.
    char** arg_ary - The array that stores the initial command + arguments.
  Returns:
    The file descriptors of the redirected stdin/stdout, or NULL if not redirected.
*/
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

/*
  Description:
    Executes a program via forking (or changing directory if the command is cd.)
  Parameters:
    char** args - Command + argument array to be executed.
  Returns:
    void
*/
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

/*
  Description:
    Parses a line from stdin and performs any piping/redirect/execution
  Parameters:
    char* line - Line to be parsed
  Returns:
    0 if the execution is successful, errno if not.
*/
int parseCommands(char *line) {
  while(line != NULL) {
    char * secondCommand = NULL;
    secondCommand = strsep(&line, ";");

    char * firstCommand = NULL;
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

    int* pipeDescrs = NULL;
    if(secondCommand != NULL) {
      pipeDescrs = redirect("tf3301.txt", 1);
    }

    char * args[16];
    int* descrs = parse_args(firstCommand, args);
    exec(args);
    if(descrs != NULL) {
      dup2(descrs[1], descrs[0]);
    }

    if(secondCommand != NULL) {
      dup2(pipeDescrs[1], pipeDescrs[0]);
      pipeDescrs = redirect("tf3301.txt", 0);
      descrs = parse_args(secondCommand, args);
      exec(args);
      if(descrs != NULL) {
        dup2(descrs[1], descrs[0]);
        free(descrs);
      }
      dup2(pipeDescrs[1], pipeDescrs[0]);
    }

    if(pipeDescrs != NULL) {
      free(pipeDescrs);
    }
  }
  return errno;
}
