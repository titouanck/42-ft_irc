NAME := ircserv

SRCDIR := srcs
INCDIR := inc
OBJDIR := objs

SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

CXX := c++
CXXFLAGS :=  -std=c++98 -Wall -Wextra -Werror -I$(INCDIR) -MMD

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
	docker run -v ./:/app your_image_name

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re
