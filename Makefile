SRC = minishell.c signals.c echo.c pwd.c cd.c expand_args.c env.c export.c\
	  exit.c executable.c

NAME = minishell
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror
READLINE_DIR = ~/homebrew/Cellar/readline/8.1.1

all: libft $(NAME)

$(NAME): $(SRC) $(LIBFT) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(LIBFT) -I $(READLINE_DIR)/include/ -L $(READLINE_DIR)/lib/ -lreadline -o $(NAME)

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
