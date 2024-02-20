NAME = ircserv
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98

SRCS_DIRS ?= srcs/classes srcs/commands srcs/connections srcs/core srcs/utils

SRCS_FILES = $(foreach dir,$(SRCS_DIRS),$(wildcard $(dir)/*.cpp))

INC_PATH = inc
HPP_FILES = $(wildcard $(INC_PATH)/*.hpp)
TPP_FILES = $(wildcard $(INC_PATH)/*.tpp)
H___FILES = $(wildcard $(INC_PATH)/*.h)

OBJS_PATHS = $(foreach dir,$(SRCS_DIRS),objs/$(dir))
OBJS_FILES = $(patsubst %.cpp,objs/%.o,$(SRCS_FILES))

DEPENDENCIES = Makefile $(HPP_FILES) $(TPP_FILES) $(H___FILES)

# ********************************************************************** #

all: $(NAME)

$(NAME): $(OBJS_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBS) -I $(INC_PATH)
	@echo "\033[0;32m[✔️] $(NAME) successfully built.\033[0m"

objs/%.o: %.cpp $(DEPENDENCIES) | $(OBJS_PATHS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -D EXECUTABLE=\"$(NAME)\"

$(OBJS_PATHS):
	@mkdir -p $@

# ********************************************************************** #

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
