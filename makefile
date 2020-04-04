CC = g++
CFLAGS = -Wall
LDFLAGS = -lm -lGLEW -lGLU -lGL -lglut 

SRC2 = utils.cpp main.cpp Object.cpp RotationHandler.cpp World.cpp Nave.cpp Camera.cpp Meteoro.cpp


all: hello
.PHONY: all

hello:  $(SRC2) makefile
	$(CC) $(CFLAGS) $(SRC2) $(LDFLAGS) -o world.out 


compile:
	g++ utils.cpp main.cpp Object.cpp RotationHandler.cpp World.cpp Nave.cpp Camera.cpp -lm -lGLEW -lGLU -lGL -lglut -o a.out

run:
	./a.out	
