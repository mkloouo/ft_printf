# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 16:41:30 by modnosum          #+#    #+#              #
#    Updated: 2018/08/20 22:49:11 by modnosum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR 		:= source
INC_DIR 		:= include
OBJ_DIR 		:= build

CC				:= gcc
TFLAGS			:= -g
CFLAGS			:= -Wall -Werror -Wextra -pedantic $(TFLAGS)
IFLAGS			:= -I $(INC_DIR)
LFLAGS			:= -l ftprintf -L .

NAME			:= libftprintf.a

IS_NORM_ENABLED	:= $(shell command -v norminette)

SRCS			:= $(shell find $(SRC_DIR) -type f -name "*.c")
DIRS			:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(shell find $(SRC_DIR) -type d))
OBJS			:= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

.PHONY: all clean fclean re test f c n t 

all: $(NAME)

clean:
	@rm -fR $(OBJ_DIR)
	@rm -fR test*
	@echo "Partially cleaned up."

fclean: clean
	@rm -fR $(NAME)
	@echo "Cleaned all."

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

$(OBJ_DIR):
	@mkdir -p $(DIRS)

$(NAME): $(OBJS)
	@ar -crs $@ $^
	@echo "Done."

test: main.c | $(NAME)
	@$(CC) -o $@ $(IFLAGS) $(LFLAGS) $(TFLAGS) $^
	@echo "Made test."

t: test

norm:
ifeq (,$(IS_NORM_ENABLED))
	@echo "no norminette on your pc"
else
	@find . -type f -name "*.[ch]" -exec norminette {} \+
endif

n: norm
c: clean
f: fclean
