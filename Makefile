CC = g++ 
CC_FLAGS = -std=c++2a -O3 -g
CLS = clear
SC = source/

all:
	${CC} ${CC_FLAGS} -c ${SC}*.cc
	${CC} ${CC_FLAGS} -o topo *.o

clean:
	rm *.o
	rm topo