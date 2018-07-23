CC := gcc
CFLAGS := -g #-Wall -Werror -Wextra -pedantic
IFLAGS := -I ./inc

NAME := libftprintf.a

SRCS := $(shell find src -type f -name "*.c")
SRCS += $(shell find inc -type f -name "*.h")

DIRS := $(patsubst src%,build%,$(shell find src -type d))

OBJS := $(patsubst inc%,build%.gch,$(patsubst src%.c,build%.o,$(SRCS)))

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -fR build/

fclean: clean
	rm -fR $(NAME)

re: fclean all

build/%.o: src/%.c | build
	$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

build/%.h.gch: inc/%.h | build
	$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS)

build:
	mkdir -p $(DIRS)

$(NAME): $(OBJS)
	ar -crs $@ $^

test: test.c $(NAME)
	$(CC) $(CFLAGS) -o $@ $(IFLAGS) $^
