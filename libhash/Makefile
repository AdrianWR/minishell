	# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/12 14:32:55 by aroque            #+#    #+#              #
#    Updated: 2020/12/30 23:40:27 by aroque           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	libhash.a

CC			=	clang
CC_FLAGS	=	-Wall	\
				-Wextra	\
				-Werror	\
				-g


INCLUDE	=	./include

SRC_DIR	=	./src
SRC		=	${SRC_DIR}/hash.c			\
			${SRC_DIR}/ht_create.c		\
			${SRC_DIR}/ht_set.c			\
			${SRC_DIR}/ht_get.c			\
			${SRC_DIR}/ht_remove.c		\
			${SRC_DIR}/ht_free.c

TEST_DIR=	./test
TEST_SRC=	$(TEST_DIR)/test.c

OBJ_DIR	=	./build
OBJ		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

override CC_FLAGS += -I$(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(CC_FLAGS) -I$(TEST_DIR) $(TEST_SRC) $< -o test_exec
	./test_exec
	$(RM) ./test_exec

.PHONY: clean test
