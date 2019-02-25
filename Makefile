# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/14 16:41:35 by glavigno          #+#    #+#              #
#    Updated: 2019/01/29 16:28:09 by glavigno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC_FILES = main.c \
			get_next_line.c \
			check_gnl.c matrix.c \
			do_room_name_and_coord.c\
			pathfinder.c \
			resolve.c \
			resolve_utils.c \
			utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)
LIB_NAME = libft.a

SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = libft

SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_FILES))
LIB = $(addprefix $(LIB_PATH)/,$(LIB_NAME))

CC = gcc
CFLAGS = -Werror -Wall -Wextra

GREEN = \033[32m
RED = \033[31m
END = \033[0m

all: LIB_C $(NAME)

LIB_C:
	@make -C $(LIB_PATH)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LIB) $(OBJ) -o $@ 
	@echo "$(GREEN)$(NAME) ready to be executed ✓$(END)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) && make clean -C $(LIB_PATH)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED).o files deleted ✗$(END)"

fclean: clean
	@rm -f $(NAME) && make fclean -C $(LIB_PATH)
	@echo "$(RED)$(NAME) deleted ✗$(END)"

re: fclean all

.PHONY: all clean fclean re
