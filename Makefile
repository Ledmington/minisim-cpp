CC=g++
CFLAGS=-Wall -Werror -Wpedantic
SFML=-lsfml-graphics -lsfml-window -lsfml-system

default: clean build check

build:
	${CC} ${CFLAGS} src/*.cpp -o out/main ${SFML}
	${CC} ${CFLAGS} test/*.cpp -o out/test ${SFML}

check:
	./out/test

run:
	./out/main

clean:
	rm out/*
