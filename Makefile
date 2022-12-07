CC = gcc
SRC = $(wildcard src/*.c)
OBJ  = $(SRC:%.c=%.o)
CFLAGS = -Wall -Werror -Wextra -pedantic
NAME = maze

.PHONY: all clean

all: $(OBJ)
	$(CC) $^ -lm `sdl2-config --libs` -o $(NAME)
	make clean

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ `sdl2-config --cflags`

clean:
	$(RM) -f $(OBJ)
