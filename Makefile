CC=g++
CFLAGS=-Wall -Werror -Wpedantic
SFML=-lsfml-graphics -lsfml-window -lsfml-system

default: build

build:
	${CC} ${CFLAGS} main.cpp -o out/main ${SFML}

run:
	./out/main

clean:
	rm out/*
