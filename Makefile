CC = gcc
CFLAGS = -std=gnu89 -Wall -Werror -Wextra -pedantic -w
SRC = main.c execute.c _strsplit.c helpers.c _strchr.c io.c shell_logic.c path.c shell.c \
      builtin_cd.c builtin_setenv.c builtin_unsetenv.c env.c env_builtins.c \
      env_init.c env_utils.c memory.c set.c set_fns.c set_ops.c string_compare.c \
      vector.c signal_handler.c shell_exit.c exit_utils.c puts.c


OBJ = $(SRC:.c=.o)
NAME = hsh

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

