FLAGS = -Wall -Werror -Wextra

NAME = libft.a

CC = gcc

OBJS = $(FILES:.c=.o)

OBJS_BONUS = $(FILES_BONUS:.c=.o)

FILES =	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strcmp.c\
		ft_strcmp_multi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_substr.c\
		ft_substr_free.c\
		ft_strjoin.c\
		ft_strjoin_free.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_numlen.c\
		ft_realloc.c\
		ft_count_strs.c\
		ft_free_ptr_array.c\
		ft_strtrim_free.c\
		ft_skip.c\
		ft_skip_until.c\
		ft_memdup.c\
		ft_recalloc.c\

FILES_BONUS =	ft_lstnew_bonus.c\
				ft_lstadd_front_bonus.c\
				ft_lstsize_bonus.c\
				ft_lstlast_bonus.c\
				ft_lstadd_back_bonus.c\
				ft_lstdelone_bonus.c\
				ft_lstclear_bonus.c\
				ft_lstiter_bonus.c\
				ft_lstmap_bonus.c\

ifdef BONUS
RELEVANT_OBJS = $(OBJS) $(OBJS_BONUS)
else
RELEVANT_OBJS = $(OBJS)
endif

%.o : %.c libft.h
		@$(CC) $(FLAGS) -c $<
		@echo "Compiling $<"

$(NAME): $(RELEVANT_OBJS)
	@ar -cr $(NAME) $(RELEVANT_OBJS)
	@echo "Creating archive file"

all: $(NAME)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo "Removing object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Removing archive file"

re: fclean all

bonus:
	@$(MAKE) BONUS=1

.PHONY: all clean fclean re bonus
