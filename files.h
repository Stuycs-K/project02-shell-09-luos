#ifndef DIRECTORY_H
#define DIRECTORY_H
void changeDir(char **args);
int* redirect(char *path, int inOut);
int checkRedirect(char **arg_ary, int size);
#endif
