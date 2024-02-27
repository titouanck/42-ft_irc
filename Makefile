NAME := ircserv

SRCDIR := srcs
INCDIR := inc
OBJDIR := objs

SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

CXX := c++
CXXFLAGS := -g -std=c++98 -Wall -Wextra -Werror -I$(INCDIR) -MMD

# ********************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $^ $(LIBS) -I $(INCDIR)
	@echo "\033[0;32m[✔️] $(NAME) successfully built.\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $(shell echo "$<" | sed 's/$(SRCDIR)\///')
	@$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

# ********************************************************************** #

clean:
	rm -rf objs
	rm -rf deps

docker:
	docker kill ircserv || true
	mkdir -p srcs/
	mkdir -p inc/
	mkdir -p objs/
	sudo docker-compose build
	sudo docker-compose up -d
	sudo docker exec -it ircserv sh

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re
