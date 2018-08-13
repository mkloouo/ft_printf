# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 16:41:30 by modnosum          #+#    #+#              #
#    Updated: 2018/08/13 16:42:16 by modnosum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
IFLAGS = -I $(INC_DIR)

NAME := libftprintf.a

SRC_DIR := sources
INC_DIR := includes
OBJ_DIR := objects

SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
DIRS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(shell find $(SRC_DIR) -type d))
OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -fR $(OBJ_DIR)

fclean: clean
	rm -fR $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

$(OBJ_DIR):
	mkdir -p $(DIRS)

$(NAME): $(OBJS)
	ar -crs $@ $^
