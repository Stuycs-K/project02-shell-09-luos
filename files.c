#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
  Description:
    Changes the current directory.
  Parameters:
    char** args - Command + argument array.
  Returns:
    void
*/
void changeDir(char **args) {
  char *arg = args[1];
  if(arg == NULL) {
    arg = getenv("HOME");
  }
  int number = chdir(arg);
  if(number < 0) {
      perror("cd failed\n");
      exit(-1);
  }
}

/*
  Description:
    Redirects stdin/stdout.
  Parameters:
    char* path - Path for stdin/stdout to be redirected to
    int redir - 0 if stdin, 1 if stdout
  Returns
    A dynamically-allocated array of the new file descriptor to the path and a backup
    file descriptor of stdin/stdout.
*/
int* redirect(char *path, int redir) {
  int fd = -1;
  if (redir == 0) {
    fd = open(path, O_RDONLY);
  }
  else if (redir == 1) {
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0650);
  }
  if (fd < 0) {
    perror("failed file open\n");
    exit(-1);
  }
  int out = redir;
  int backup = dup(out);
  dup2(fd, out);

  int* descrs = malloc(2*sizeof(int));
  descrs[0] = out;
  descrs[1] = backup;
  return descrs;
}

/*
  Description:
    Check if a line contains a redirect mechanism and automatically terminates an argument
    array with NULL if so.
  Parameters:
    char* buffer - The line to be parsed.
    char** arg_ary - The command + argument array.
    int i - The current index of the array.
  Returns:
    0 if stdin, 1 if stdout, -1 if no redirect mechanism is detected.
*/
int checkRedirect(char *buffer, char **arg_ary, int i) {
  if (strcmp(buffer, "<") == 0) {
    arg_ary[i] = NULL;
    return 0;
  }
  else if (strcmp(buffer, ">") == 0) {
    arg_ary[i] = NULL;
    return 1;
  }
  return -1;
}
