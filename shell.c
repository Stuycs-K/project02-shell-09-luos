#include <stdio.h>
#include <string.h>

int LINE_SIZE = 100;

int main() {
  char line[LINE_SIZE];
  for (int i = 0; i < LINE_SIZE; i++) {
    line[i] = 0;
  }
  if(fgets(&line, LINE_SIZE, stdin) == -1) {
    if(strcmp(line, "quit") == 0) {
      printf("QUIT");
      return 0;
    }
  }
}
