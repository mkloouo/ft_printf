CC := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic
IFLAGS := -I ./inc

NAME := libftprintf.a

SRCS := $(shell find src -type f -name "*.c")
DIRS := $(patsubst src%,build%,$(shell find src -type d))
OBJS := $(patsubst src%.c,build%.o,$(SRCS))

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -fR build/

fclean: clean
	rm -fR $(NAME)

re: fclean all

build/%.o: src/%.c | build
	$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

build:
	mkdir -p $(DIRS)

$(NAME): $(OBJS)
	ar -crs $@ $^
