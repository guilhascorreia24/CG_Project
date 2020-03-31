CC = g++
CFLAGS = -Wall
LDFLAGS = -lm -lGLEW -lGLU -lGL -lglut 

SRC2 = utils.cpp main.cpp Object.cpp RotationHandler.cpp World.cpp

all: hello
.PHONY: all

hello:  $(SRC2) makefile
	$(CC) $(CFLAGS) $(SRC2) $(LDFLAGS) -o world.out 