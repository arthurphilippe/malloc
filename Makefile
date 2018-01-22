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

SRCS		=	src/my_malloc.c

SRCS_TEST	=	main.c

OBJS		=	$(SRCS:.c=.o)

OBJS_TEST	=	$(SRCS_TEST:.c=.o)

CFLAGS		=	-W -Wextra -Wall -Iinclude/

all: $(NAME)

debug: CFLAGS += -ggdb
debug: $(NAME) $(NAME_TEST)

debugre: CFLAGS += -ggdb
debugre: fclean
debugre: $(NAME) $(NAME_TEST)

$(NAME_TEST): $(OBJS_TEST)
	$(CC) $(OBJS_TEST) -o $(NAME_TEST) -L. -lmy_malloc

$(NAME): $(OBJS)
	$(CC) $(OBJS) -shared -fPIC -o $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_TEST)

fclean: clean
	$(RM) $(NAME) $(NAME_TEST)

re: fclean all

.PHONY: all clean fclean re
