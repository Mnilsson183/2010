CC=g++
SRC_FILES = main.cpp
FLAGS = -Wall -Wextra -Werror -g -std=c++11
CURSES = -lcurses
OBJ_FILES = $(SRC_FILES:.cpp=.o)
EXEC = a.out

all:
	${CC} ${FLAGS} -c ${SRC_FILES}
	${CC} ${OBJ_FILES} ${FLAGS} ${CURSES} -o ${EXEC}
	@echo 'removing all object files ...'
	rm ${OBJ_FILES}
	@echo 'builing to ${EXEC}'
run: all
	./a.out
clean:
	rm ${EXEC} ${OBJ_FILES}
