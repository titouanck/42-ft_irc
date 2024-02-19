# NAME = ircserv
# CC = c++
# CFLAGS = -g -Wall -Wextra -Werror -std=c++98

# # ********************************************************************** #

# SRCS_PATH = srcs/
# SRCS_FILES = $(shell find srcs/ -name '*.cpp' -exec basename {} \;)

# INC_PATH = inc/
# HPP_FILES = $(shell find inc/ -name '*.hpp' -exec basename {} \;)
# TPP_FILES = $(shell find inc/ -name '*.tpp' -exec basename {} \;)
# H___FILES = $(shell find inc/ -name '*.h'   -exec basename {} \;)

# OBJS_PATH = objs/
# OBJS_FILES = ${patsubst %.cpp, ${OBJS_PATH}/%.o, ${SRCS_FILES}}

# DEPENDENCIES = Makefile
# DEPENDENCIES += $(shell echo ${HPP_FILES} | sed 's/[^ ]* */inc\/&/g')
# DEPENDENCIES += $(shell echo ${TPP_FILES} | sed 's/[^ ]* */inc\/&/g')
# DEPENDENCIES += $(shell echo ${H___FILES} | sed 's/[^ ]* */inc\/&/g')

# vpath %.cpp ${SRCS_PATH}

# # ********************************************************************** #

# all: ${NAME}

# ${NAME}:  ${OBJS_FILES}
# 	@${CC} ${CFLAGS} -o ${NAME} ${OBJS_FILES} ${LIBS} -I ${INC_PATH}
# 	@echo "\033[0;32m[✔️] ${NAME} successfully built.\033[0m"

# ${OBJS_FILES}: ${OBJS_PATH}/%.o: %.cpp ${DEPENDENCIES}
# 	@mkdir -p ${OBJS_PATH}
# 	@${CC} ${CFLAGS} -c $< -o $@ -I ${INC_PATH} -D EXECUTABLE=\"$(NAME)\"

# # ********************************************************************** #

# clean:	
# 	rm -rf ${OBJS_PATH}

# fclean:	clean;
# 	rm -f ${NAME}

# re:	fclean ${NAME}

# .PHONY: all clean fclean re
NAME = ircserv
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98

# ********************************************************************** #

SRCS_PATH = srcs/ src/
SRCS_FILES = $(shell find $(SRCS_PATH) -name '*.cpp' -exec basename {} \;)

INC_PATH = inc/
HPP_FILES = $(shell find $(INC_PATH) -name '*.hpp' -exec basename {} \;)
TPP_FILES = $(shell find $(INC_PATH) -name '*.tpp' -exec basename {} \;)
H___FILES = $(shell find $(INC_PATH) -name '*.h'   -exec basename {} \;)

OBJS_PATH_SRCS = objs/srcs/
OBJS_PATH_SRC = objs/src/
OBJS_FILES = $(patsubst %.cpp,$(OBJS_PATH_SRCS)%.o,$(filter $(SRCS_PATH)srcs/%,$(SRCS_PATH)$(SRCS_FILES))) \
             $(patsubst %.cpp,$(OBJS_PATH_SRC)%.o,$(filter $(SRCS_PATH)src/%,$(SRCS_PATH)$(SRCS_FILES)))

DEPENDENCIES = Makefile
DEPENDENCIES += $(addprefix $(INC_PATH),$(HPP_FILES)) $(addprefix $(INC_PATH),$(TPP_FILES)) $(addprefix $(INC_PATH),$(H___FILES))

# ********************************************************************** #

all: $(NAME)

$(NAME):  $(OBJS_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS_FILES) $(LIBS) -I $(INC_PATH)
	@echo "\033[0;32m[✔️] $(NAME) successfully built.\033[0m"

$(OBJS_PATH_SRCS)%.o: %.cpp $(DEPENDENCIES)
	@mkdir -p $(OBJS_PATH_SRCS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -D EXECUTABLE=\"$(NAME)\"

$(OBJS_PATH_SRC)%.o: %.cpp $(DEPENDENCIES)
	@mkdir -p $(OBJS_PATH_SRC)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -D EXECUTABLE=\"$(NAME)\"

# ********************************************************************** #

clean:
	rm -rf $(OBJS_PATH_SRCS) $(OBJS_PATH_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
