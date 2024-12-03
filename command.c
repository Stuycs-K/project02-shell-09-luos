#include <stdio.h>
#include <string.h>

int parseCommands(char *line) {
  while(line != NULL) {
    char * command;
    command = strsep(&line, ";");
    printf("%s\n", command);
  }
  return 0;
}
