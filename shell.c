#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"

#define LINE_SIZE 100

/*
  Name:
    main
  Description:
    Prompts the user, reads from stdin (or a file), and executes commands.
  Parameters:
    None
  Returns:
    0 if successful, errno if not.
*/
int main() {
  char line[LINE_SIZE];
  while(1) {
    for (int i = 0; i < LINE_SIZE; i++) {
      line[i] = 0;
    }

    char buffer[LINE_SIZE];
    getcwd(buffer, LINE_SIZE);
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
