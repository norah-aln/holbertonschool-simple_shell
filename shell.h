#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* String functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);

/* Main shell function */
void execute_command(char *command, char **argv);

#endif
