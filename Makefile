NAME	= pamela.so

SRC		= src/pamela.c

OBJ		= $(SRC:.c=.o)

CC		= gcc

CFLAGS	+= -fPIC -I ./include

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -shared $(OBJ)

install:

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all install clean fclean re