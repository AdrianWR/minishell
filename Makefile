NAME	=	minishell
RM		=	/bin/rm -f
MODULES	=	$(LIB_DIR)
CC		=	clang
CC_FLAG =	-c		\
			-Wall	\
			-Wextra	\
			-Werror
INCLUDE	=	-I ./includes	\
			-I $(LIB_DIR)	\
			-I $(GNL_DIR)

LIB_DIR	=	./libft
LIB		=	$(LIB_DIR)/libft.a

GNL_DIR	=	./gnl
GNL_SRC	=	$(GNL_DIR)/get_next_line.c			\
			$(GNL_DIR)/get_next_line_utils.c

MSH_DIR	=	./src
MSH_SRC	=	$(MSH_DIR)/main.c

SRC		=	$(GNL_SRC)	\
			$(MSH_SRC)

OBJ		=	$(patsubst %.c, %.o, ${SRC})


#-fsanitize=address
all		:	$(NAME)
$(NAME)	:	$(OBJ) $(LIB)
			$(CC) -o $@ $^
%.o		:	%.c
			$(CC) -g $(CC_FLAG) $(INCLUDE) $< -o $@ 
$(LIB)	:
			$(MAKE) -C $(LIB_DIR)
clean	:
			# for dir in $(MODULES); do	\
			# 	$(MAKE) clean -C $$dir;	\
			# done
			$(MAKE) clean -C $(LIB_DIR)
			$(RM) $(OBJ)
fclean	:	clean
			# $(MAKE) fclean -C $(LIB_DIR)
			$(RM) $(NAME)
re		:	fclean all