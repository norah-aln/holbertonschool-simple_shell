#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* ====== Prototypes ====== */
char **tokenize_line(char *line);
void free_args(char **args);
char *find_path(char *cmd, char **envp);
void execute_cmd(char *cmd_path, char **args, char **envp);
int builtin_exit(char **args);
int builtin_env(char **args, char **envp);

#endif

