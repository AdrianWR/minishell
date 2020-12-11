NAME	=	minishell

MODULES	=	$(LIB_DIR)

LIB_DIR	=	lib/libft
LIB		=	$(LIB_DIR)/libft.a

INCLUDE_DIR = include
INCLUDE =	minishell.h

SRC_DIR	=	src
SRC		=	main.c

OBJ_DIR	=	build
OBJ		=	$(patsubst %.c, ${OBJ_DIR}/%.o, ${SRC})

vpath %.c src
vpath %.h include

CC		=	clang
CC_FLAGS=	-c			\
			-Wall		\
			-Wextra		\
			-Werror		\
			-I${INCLUDE_DIR}\
			-I${LIB_DIR}
LD_FLAGS=	-L${LIB_DIR}	\
			-lft

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $< $(LD_FLAGS) -o $@

${OBJ_DIR}/%.o: %.c
	$(CC) -g $(CC_FLAGS) $< -o $@ 

${LIB}:
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) clean -C $(LIB_DIR)
	$(RM) $(OBJ)
fclean:	clean
	$(MAKE) fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re:	fclean all

test: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re
