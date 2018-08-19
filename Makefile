# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 16:41:30 by modnosum          #+#    #+#              #
#    Updated: 2018/08/19 10:25:05 by modnosum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
IFLAGS = -I $(INC_DIR)

NAME := libftprintf.a

SRC_DIR := source
INC_DIR := include
OBJ_DIR := build

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

IS_NORM_ENABLED := $(shell command -v norminette)
norm:
ifeq (,$(IS_NORM_ENABLED))
	@echo "no norminette on your pc"
else
	@find . -type f -name "*.[ch]" -exec norminette {} \+
endif
