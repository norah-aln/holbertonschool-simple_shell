#include "shell.h"

char **parse_input(char *input)
{
char **args;
char *token;
int i = 0;
int bufsize = 64;

args = malloc(sizeof(char *) * bufsize);
if (!args)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(input, " \t");
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " \t");
}
args[i] = NULL;

return args;
}
