CC=g++
CFLAGS=-Wall -Werror -Wpedantic
OPT=-Ofast
SFML=-lsfml-graphics -lsfml-window -lsfml-system

default: clean build check

build:
	${CC} ${CFLAGS} ${OPT} src/*.cpp -o out/minisim ${SFML}
	${CC} ${CFLAGS} test/*.cpp -o out/test ${SFML}

check:
	./out/test

run:
	./out/minisim

todo:
	find . | grep .*pp$$ | grep -rnw . -e TODO

clean:
	rm out/*
