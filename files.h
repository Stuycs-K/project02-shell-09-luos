#ifndef DIRECTORY_H
#define DIRECTORY_H
void changeDir(char **args);
int* redirect(char *path, int redir);
int checkRedirect(char *buffer, char **arg_ary, int i);
#endif
