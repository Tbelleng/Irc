NAME 		=	ircserv

SRCS 		=   server.cpp \
				main.cpp	\

OBJS		=		$(SRCS:.cpp=.o)
INCLUDE		= 		./
AR		=		#ar rcs
RM		=		rm -f
CC		=		c++ 
CFLAGS		=	-std=c++98 -Wall -Wextra -Werror

%.o:				%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

all:	$(NAME)

$(NAME):		$(OBJS)
	@clear
	@echo "\033[1;34m"
	@echo "Project name : $(NAME)"
	@echo "\n\033[1;32mCompilation... ⌛\033[0;m\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@make wait

clean:
	@$(RM) $(OBJS)
	@echo "\033[1;1;32m♻️  Objects have been \033[5;1;31mdeleted\033[m ♻️"

fclean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@echo -n "\033[0;31m⠀"
	@echo "[##############]"
	@echo "\033[1;1;32m♻️  Objects and $(NAME) have been \033[5;1;31mdeleted\033[m ♻️"

wait:
	@echo -n "\r  5%  [\033[0;31m█\033[m.........................]"
	@sleep 0.01
	@echo -n "\r 10%  [\033[0;31m███\033[m.......................]"
	@sleep 0.01
	@echo -n "\r 15%  [\033[0;31m████\033[m......................]"
	@sleep 0.01
	@echo -n "\r 20%  [\033[0;31m██████\033[m....................]"
	@sleep 0.01
	@echo -n "\r 35%  [\033[0;31m███████████\033[m...............]"
	@sleep 0.01
	@echo -n "\r 45%  [\033[0;31m█████████████\033[m.............]"
	@sleep 0.01
	@echo -n "\r 50%  [\033[0;31m███████████████\033[m...........]"
	@sleep 0.01
	@echo -n "\r 65%  [\033[0;31m██████████████████\033[m........]"
	@sleep 0.01
	@echo -n "\r 80%  [\033[0;31m█████████████████████\033[m.....]"
	@sleep 0.01
	@echo -n "\r 90%  [\033[0;31m████████████████████████\033[m..]"
	@sleep 0.01
	@echo -n "\r 95%  [\033[0;31m█████████████████████████\033[m.]"
	@sleep 0.05
	@echo -n "\r 99%  [\033[0;31m██████████████████████████\033[m]"
	@sleep 1
	@echo -n "\r 100% [\033[0;32m██████████████████████████\033[m]\033[0;32m compilation finished ✓\n\033[0;m"
re:		fclean all

.PHONY: all clean fclean re