CC=g++
SRC_FILES = main.cpp
FLAGS =  -std=c++11 -Wall -Wextra -Werror -g
LINKER = -lcurses
OBJ_FILES = $(SRC_FILES:.cpp=.o)
EXEC = a.out

CPP_CHECK_FLAGS = --check-level=exhaustive
CPP_LINT_FLAGS = --filter=-whitespace/tab

all:
	${CC} ${FLAGS} -c ${SRC_FILES}
	${CC} ${OBJ_FILES} ${FLAGS} ${LINKER} -o ${EXEC}
	@echo 'builing to ${EXEC}'

full: check all
	@echo 'Full build'

run: all
	./a.out

check:
	cppcheck ${CPP_CHECK_FLAGS} ${SRC_FILES}
	cpplint ${CPP_LINT_FLAGS} ${SRC_FILES} 

clean:
	rm ${EXEC} ${OBJ_FILES}

valgrind: all
	valgrind ${EXEC}
