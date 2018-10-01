# minishell
This is an introductory Unix project, the objective is to implement a basic Unix shell which handles simple system commends (mostly done through look up within PATH in env).

## Compiling and running
Run `make`. An executable will compile. Currently only tested on OS X.

Run with `./minishell`.

## Functions used

* malloc, free

* access

* open, close, read, write

* getcwd, chdir

* fork, execve

* wait, waitpid, wait3, wait4

* exit

## Features

* Displays prompt "😃$> " and wait till you type a command line, validated by pressing enter

* The prompt is shown again only once the command has been completely executed

* The command lines are simple, no pipes, no redirections or any other advanced functions

* The executable are those you can find in the paths indicated in the PATH variable

* Shows error message in cases where the executable cannot be found, and display the prompt again

* Manage errors without using errno, by displaying a message adapted to the error output

* Manage PATH and the environment (copy of system char **environ) both locally and linked to the system

* Implemented a series of builtins: echo, cd, setenv, unsetenv, env and exit locally

* Manages expansions $ and ˜

