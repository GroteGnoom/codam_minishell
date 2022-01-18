SRC = minishell.c signals.c echo.c pwd.c cd.c expand_args.c env.c export.c\
	  exit.c executable.c unset.c pipex.c pipex_child.c\
	  quote_split.c redirect.c here_doc.c path_utils.c wildcard.c\
	  expand_wildcard.c is_built_in.c shell_split.c split_unquoted.c\
	  error_msg.c shell_split_utils.c print_utils.c copy_env.c\
	  expand_args_utils.c print_line_nr.c error_syntax.c commands.c\
	  check_special.c here_doc_utils.c

NAME = minishell
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = get_next_line
GNL = $(GNL_DIR)/get_next_line.a
ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
ifdef LEAKS
	FLAGS = -Wall -Wextra -g
else
	FLAGS = -Wall -Wextra -g -fsanitize=address
endif
endif

READLINE_DIR = ~/homebrew/Cellar/readline/8.1.1

all: libft gnl $(NAME)

$(NAME): $(SRC) $(GNL) $(LIBFT) $(NAME).h
ifndef DEBUG
	gcc $(FLAGS) -I. $(SRC) $(GNL) $(LIBFT) -I $(READLINE_DIR)/include/ -L $(READLINE_DIR)/lib/ -lreadline -o $(NAME)
else
	clang $(FLAGS) -I. $(SRC) $(GNL) $(LIBFT) -I $(READLINE_DIR)/include/ -L $(READLINE_DIR)/lib/ -lreadline -o $(NAME)
endif

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

gnl:
	$(MAKE) -C $(GNL_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
