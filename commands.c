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
  while(curr != NULL) {
    buffer = strsep(&curr, " ");
    arg_ary[i] = buffer;
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

int parseRedirect(char *line) {
  char * command = NULL;
  char * path = line;

  int redir = -1;
  // https://stackoverflow.com/questions/12784766/check-substring-exists-in-a-string-in-c
  if(strstr(path, " < ") != NULL) {
    command = strsep(&path, " < ");
    path = path + 2;
    redir = 0;
  }
  else if(strstr(path, " > ") != NULL) {
    command = strsep(&path, " > ");
    path = path + 2;
    redir = 1;
  }
  else if(strstr(path, "<") != NULL) {
    command = strsep(&path, "<");
    redir = 0;
  }
  else if(strstr(path, ">") != NULL) {
    command = strsep(&path, ">");
    path = path + 2;
    redir = 1;
  }
  else {
    command = line;
    path = NULL;
  }

  int* descrs = NULL;
  if(path != NULL) {
    descrs = redirect(path, redir);
  }
  char * args[16];
  parse_args(command, args);
  exec(args);
  if(path != NULL) {
    dup2(descrs[1], descrs[0]);
    free(descrs);
  }
  return errno;
}

int parsePipe(char *line) {
  char * command1 = NULL;
  char * command2 = line;
  // https://stackoverflow.com/questions/12784766/check-substring-exists-in-a-string-in-c
  if(strstr(command2, " | ") != NULL) {
    command1 = strsep(&command2, " | ");
    command2 = command2 + 2;
  }
  else if(strstr(command2, "|") != NULL) {
    command1 = strsep(&line, "|");
  }
  else {
    command1 = line;
    command2 = NULL;
  }

  int* descrs = NULL;
  if(command2 != NULL) {
    descrs = redirect("tf3301.txt", 1);
  }
  parseRedirect(command1);
  if(command2 != NULL) {
    dup2(descrs[1], descrs[0]);
    descrs = redirect("tf3301.txt", 0);
    parseRedirect(command2);
    dup2(descrs[1], descrs[0]);
    free(descrs);
  }
  return errno;
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
    char * commandBlock = strsep(&line, ";");
    parsePipe(commandBlock);
  }
  return errno;
}
