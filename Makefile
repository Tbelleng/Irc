NAME = ircserv

SRC_DIR = ./src/

SRCS = $(SRC_DIR)main.cpp	\
	   $(SRC_DIR)Channel.cpp	\
	   $(SRC_DIR)server.cpp	\
	   $(SRC_DIR)User.cpp	\
	   $(SRC_DIR)utils.cpp		

OBJS_DIR = ./obj/

OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJS_DIR)%.o)
DEPS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJS_DIR)%.d)
INCLUDE = ./include/
RM = rm -f
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INCLUDE)

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJS_DIR)
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(NAME): $(OBJS)
	@clear
	@echo "\033[1;34m                                                                                                                     "
	@echo "    Loading quantum version..."
	@echo "Project name: $(NAME)"
	@echo "\n\033[1;32mCompilation... ⌛\033[0;m\n"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo -n "\r 5%  [\033[0;31m█\033[m.........................]"
	@sleep 0.01
	@echo -n "\r 10%  [\033[0;31m███\033[m.......................]"
	@sleep 0.01
	@echo -n "\r 15%  [\033[0;31m████\033[m......................]"
	@sleep 0.01
	@echo -n "\r 20%  [\033[0;31m██████\033[m....................]"
	@sleep 0.01
	@echo -n "\r 27%  [\033[0;31m████████\033[m..................]"
	@sleep 0.01
	@echo -n "\r 32%  [\033[0;31m██████████\033[m................]"
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

-include $(DEPS)

clean:
	@echo "\033[1;1;32m♻️  Objects have been \033[5;1;31mdeleted\033[m ♻️"
	@$(RM) -r $(OBJS_DIR)

fclean:
	@$(RM) $(NAME)
	@echo -n "\033[0;31m⠀"
	@echo "[##############]"
	@echo "\033[1;1;32m♻️  Objects and $(NAME) have been \033[5;1;31mdeleted\033[m ♻️"
	@$(RM) -r $(OBJS_DIR)

re:	fclean all

.PHONY: all clean fclean re