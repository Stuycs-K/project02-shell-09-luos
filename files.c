#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*
  Name:
    changeDir
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
  Name:
    redirect
  Description:
    Redirects a file descriptor.
  Parameters:
    char* path - Path for stdin/stdout to be redirected to
    int redir - 0 if stdin, 1 if stdout (technically can be any file descriptor)
  Returns
    A dynamically-allocated array of the new file descriptor to the path and a backup
    file descriptor of redir
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
  Name:
    exec
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
