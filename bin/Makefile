CC = g++ 
PROG = topo
CC_FLAGS_DEBUG = -Wall -Wextra -pedantic 
CC_FLAGS_DEBUG2 = -Wshadow  -Wunreachable-code -fsanitize=address -g
SANITIZE = -fsanitize=address -g
CC_FLAGS = -std=c++2a -O3
SC = ../source/

all:
	${CC} ${CC_FLAGS} -c ${SC}*.cc
	${CC} ${CC_FLAGS} -o ${PROG} *.o
debug:
	${CC} ${CC_FLAGS} ${CC_FLAGS_DEBUG} ${CC_FLAGS_DEBUG2} -c ${SC}*.cc
	${CC} ${CC_FLAGS} ${CC_FLAGS_DEBUG} ${CC_FLAGS_DEBUG2} -o ${PROG} *.o
s:
	${CC} ${CC_FLAGS} ${SANITIZE} -c ${SC}*.cc
	${CC} ${CC_FLAGS} ${SANITIZE} -o ${PROG} *.o

clean:
	rm *.o
	rm ${PROG}