IDIR =./include
SRC =./src/
CC=g++
FLAGS=-std=c++11

all:
	${CC} -o bTree ${SRC}* -I ${IDIR} ${FLAGS}
