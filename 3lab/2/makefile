CC=g++
SRC_FILES = main.cpp
FLAGS = -Wall -Wextra -Werror -g
OBJ_FILES = $(SRC_FILES:.cpp=.o)
EXEC = a.out

all:
	${CC} ${FLAGS} -c ${SRC_FILES}
	${CC} ${OBJ_FILES} -o ${EXEC}
	@echo 'removing all object files ...'
	rm ${OBJ_FILES}
	@echo 'builing to ${EXEC}'
run: all
	./a.out
clean:
	rm ${EXEC} ${OBJ_FILES}
