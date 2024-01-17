NAME = ft_irc
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

# ********************************************************************** #

SRCS_PATH = srcs/
SRCS_FILES = $(shell find srcs/ -name '*.cpp' -exec basename {} \;)

INC_PATH = inc/
HPP_FILES = $(shell find inc/ -name '*.hpp' -exec basename {} \;)
TPP_FILES = $(shell find inc/ -name '*.tpp' -exec basename {} \;)

OBJS_PATH = objs/
OBJS_FILES = ${patsubst %.cpp, ${OBJS_PATH}/%.o, ${SRCS_FILES}}

DEPENDENCIES = Makefile
DEPENDENCIES += $(shell echo ${HPP_FILES} | sed 's/[^ ]* */inc\/&/g')
DEPENDENCIES += $(shell echo ${TPP_FILES} | sed 's/[^ ]* */inc\/&/g')

vpath %.cpp ${SRCS_PATH}

# ********************************************************************** #

all: ${NAME}

${NAME}:  ${OBJS_FILES}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS_FILES} ${LIBS} -I ${INC_PATH}
	@echo "\033[0;32m[✔️] ${NAME} successfully built.\033[0m"

${OBJS_FILES}: ${OBJS_PATH}/%.o: %.cpp ${DEPENDENCIES}
	@mkdir -p ${OBJS_PATH}
	@${CC} ${CFLAGS} -c $< -o $@ -I ${INC_PATH}

# ********************************************************************** #

clean:	
	rm -rf ${OBJS_PATH}

fclean:	clean;
	rm -f ${NAME}

re:	fclean ${NAME}

.PHONY: all clean fclean re
