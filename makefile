CC = g++
CFLAGS = -Wall
LDFLAGS = -lm -lGL -lGLU -lglut

SRC2 = world.cpp

all: hello
.PHONY: all

hello:  $(SRC2) makefile
	$(CC) $(CFLAGS) $(SRC2) $(LDFLAGS) -o world.out 