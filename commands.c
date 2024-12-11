#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "files.h"

/*
  Name:
    parseArgs
  Description:
    Parses a line containing a command and arguments into an array
  Parameters:
    char* line - A string containing the command + arguments + redirection mechanism.
    char** arg_ary - The array that stores the initial command + arguments.
  Returns:
    0 if the execution is successful, errno if not
*/
int parseArgs(char *line, char **arg_ary) {
  char *curr = line;
  char *buffer;
  int i = 0;
  while(curr != NULL) {
    buffer = strsep(&curr, " ");
    arg_ary[i] = buffer;
    i++;
  }
  arg_ary[i] = NULL;
  return errno;
}

/*
  Name:
    parseRedirect
  Description:
    Parses a line and redirect file descriptors before executing commands
  Parameters:
    char* line - Line to be parsed
  Returns:
    0 if the execution is successful, errno if not.
*/
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

/*
  Name:
    parsePipe
  Description:
    Parses a line to execute two commands separately in a pipe
  Parameters:
    char* line - Line to be parsed
  Returns:
    0 if the execution is successful, errno if not.
*/
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
    free(descrs);
    descrs = redirect("tf3301.txt", 0);
    parseRedirect(command2);
    dup2(descrs[1], descrs[0]);
    free(descrs);
  }
  return errno;
}

/*
  Name:
    parseCommands
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
