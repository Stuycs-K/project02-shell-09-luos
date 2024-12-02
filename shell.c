#include <stdio.h>
#include <string.h>

// cmds (will delete later, just here for reference):

// int chdir(const char *path); || int chdir(int fd);
// changes current working directory. either use the path name as a char array or use fd.

// char * getcwd(char *buf, size_t size); || char * getcwd(char *buf);
// 

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
