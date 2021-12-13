SRC_MANDATORY = get_next_line.c get_next_line_utils.c
SRC_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c
ifdef DO_BONUS
	SRC = $(SRC_BONUS) #don't include mandatory
else
	SRC = $(SRC_MANDATORY)
endif

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = get_next_line.a

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	gcc $(FLAGS) -c $^ -o $@ -DBUFFER_SIZE=10000

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) DO_BONUS=1

.PHONY: all clean fclean re bonus
