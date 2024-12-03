#include <errno.h>
#include <stdio.h>
#include <string.h>

int LINE_SIZE = 100;

int main() {
  char line[LINE_SIZE];
  while(1) {
    for (int i = 0; i < LINE_SIZE; i++) {
      line[i] = 0;
    }
    printf("$ ");
    fflush(stdout);

    if(fgets(line, LINE_SIZE, stdin) == NULL) {
      printf("%s\n", strerror(errno));
      return errno;
    }
    if(strcmp(line, "exit\n") == 0) {
      return 0;
    }
  }
}
