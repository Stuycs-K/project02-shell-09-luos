#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
    execvp(args[0], args);
  }
  return 0;
}
