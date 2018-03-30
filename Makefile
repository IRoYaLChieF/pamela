NAME	= pamela.so

SRC		= src/pamela_auth.c \
		  src/pamela_pass.c \
		  src/pamela_session.c

OBJ		= $(SRC:.c=.o)

CC		= gcc

CFLAGS	+= -fPIC -I ./include

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -shared $(OBJ)

install:
	@mkdir -p /lib/security
	@cp $(NAME) /lib/security/$(NAME)
	@echo "auth optional $(NAME)" >> /etc/pam.d/common-auth
	@echo "session optional $(NAME)" >> /etc/pam.d/common-session
	@echo "account optional $(NAME)" >> /etc/pam.d/common-account
	@echo "password optional $(NAME)" >> /etc/pam.d/common-password

uninstall:
	@$(RM) /lib/security/$(NAME)
	@sed -i '/auth optional $(NAME)/d' /etc/pam.d/common-auth
	@sed -i '/session optional $(NAME)/d' /etc/pam.d/common-session
	@sed -i '/account optional $(NAME)/d' /etc/pam.d/common-account
	@sed -i '/password optional $(NAME)/d' /etc/pam.d/common-password

check:
ifneq ("$(wildcard /lib/security/$(NAME))","")
	@echo "PAMela is installed"
else
	@echo "PAMela isn't installed"
endif

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all install uninstall check clean fclean re