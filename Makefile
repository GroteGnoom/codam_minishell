SRC = minishell.c signals.c echo.c pwd.c cd.c expand_args.c env.c export.c\
	  exit.c executable.c unset.c pipex.c pipex_child.c pipex_split_commands.c\
	  pipex_utils.c quote_split.c redirect.c here_doc.c path_utils.c wildcard.c

NAME = minishell
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = get_next_line
GNL = $(GNL_DIR)/get_next_line.a
ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

READLINE_DIR = ~/homebrew/Cellar/readline/8.1.1

all: libft gnl $(NAME)

$(NAME): $(SRC) $(GNL) $(LIBFT) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(GNL) $(LIBFT) -I $(READLINE_DIR)/include/ -L $(READLINE_DIR)/lib/ -lreadline -o $(NAME)

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

gnl:
	$(MAKE) bonus -C $(GNL_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
