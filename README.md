[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell
## Team Member(s):
Steven Luo
## Team Name:
Zero One
## Features:
### Implemented:
* General Functionality
* Working Directory
* Prompt
* Exiting
* Simple redirection
* Pipes with no redirection and no arguments
### Attempted/Unsuccessful:
* Pipes for every other cases
## Bugs:
## Headers:

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

/*
  Name:
    parseCommands
  Description:
    Parses a line from stdin and performs any piping/redirect/execution
  Parameters:
    char* line - Line to be parsed
  Returns:
    0 if the execution is successful, errno if not.
*/

/*
  Name:
    parsePipe
  Description:
    Parses a line to execute two commands separately in a pipe
  Parameters:
    char* line - Line to be parsed
  Returns:
    0 if the execution is successful, errno if not.
*/

/*
  Name:
    parseRedirect
  Description:
    Parses a line and redirect file descriptors before executing commands
  Parameters:
    char* line - Line to be parsed
  Returns:
    0 if the execution is successful, errno if not.
*/

/*
  Name:
    parseArgs
  Description:
    Parses a line containing a command and arguments into an array
  Parameters:
    char* line - A string containing the command + arguments + redirection mechanism.
    char** arg_ary - The array that stores the initial command + arguments.
  Returns:
    0 if the execution is successful, errno if not
*/
