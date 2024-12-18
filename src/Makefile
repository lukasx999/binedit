CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -ggdb
LIBS=-lraylib
DEPS=lib.h

all: main.o lib.o $(DEPS)
	@$(CC) $(CFLAGS) $(LIBS) $^ -o out
	@echo CC $^

%.o: %.c Makefile $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo CC $<

clean:
	rm *.o out

.PHONY: clean
