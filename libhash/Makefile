# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/12 14:32:55 by aroque            #+#    #+#              #
#    Updated: 2020/05/12 23:09:48 by aroque           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	libhash.a

CC			=	gcc
CC_FLAGS	=	-Wall	\
				-Wextra	\
				-Werror	\
				-g

INCLUDE	=	.

SRC_DIR	=	./src
SRC		=	${SRC_DIR}/hash.c			\
			${SRC_DIR}/ht_create.c		\
			${SRC_DIR}/ht_set.c			\
			${SRC_DIR}/ht_get.c			\
			${SRC_DIR}/ht_free.c		\
			${SRC_DIR}/insert_node.c

OBJ_DIR	=	./build
OBJ		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CC_FLAGS) -c -I$(INCLUDE) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
