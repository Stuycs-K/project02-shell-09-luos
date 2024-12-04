#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "command.h"

int LINE_SIZE = 100;

int main() {
  char line[LINE_SIZE];
  while(1) {
    for (int i = 0; i < LINE_SIZE; i++) {
      line[i] = 0;
    }

    char buffer[100];
    getcwd(buffer, 100);
    printf("%s $ ", buffer);
    fflush(stdout);

    if(fgets(line, LINE_SIZE, stdin) == NULL) {
      printf("exit\n");
      return errno;
    }
    // below: https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
    line[strcspn(line, "\n")] = 0;

    if(strcmp(line, "exit") == 0) {
      return 0;
    }
    parseCommands(line);
  }
}
