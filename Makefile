##
## EPITECH PROJECT, 2018
## bs malloc
## File description:
## tests
##

CC		=	gcc

NAME		=	libmy_malloc.so

NAME_TEST	=	test.out

RM		=	rm -vf

SRCS		=	src/my_malloc.c		\
			src/my_free.c		\
			src/blocks.c		\
			src/realloc.c		\
			src/calloc.c

SRCS_TEST	=	tests/main.c

OBJS		=	$(SRCS:.c=.o)

OBJS_TEST	=	$(SRCS_TEST:.c=.o)

CFLAGS		=	-W -Wextra -Wall -Iinclude/ -fPIC

all: $(NAME)

debug: fclean
debug: CFLAGS += -ggdb
debug: $(NAME) $(NAME_TEST)

$(NAME_TEST): $(OBJS_TEST)
	$(CC) $(OBJS_TEST) -o $(NAME_TEST) -L. -lmy_malloc

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS) $(OBJS_TEST)

fclean: clean
	@$(RM) $(NAME) $(NAME_TEST)

re: fclean all

.PHONY: all clean fclean re
