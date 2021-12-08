SRC = minishell.c signals.c echo.c pwd.c cd.c

NAME = minishell
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror

all: libft $(NAME)

$(NAME): $(SRC) $(LIBFT) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(LIBFT) -lreadline -o $(NAME)

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
