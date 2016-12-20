CC = g++
CFLAGS = -std=c++11 -Wall

OBJS = main.o RTree.o

rtree: ${OBJS}
	${CC} ${CFLAGS} -o rtree ${OBJS} ${LIBS}

main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp ${LIBS}

RTree.o: RTree.cpp RTree.h 
	${CC} ${CFLAGS} -c RTree.cpp

clean:
	rm -f rtree ${OBJS}
	@echo "all cleaned up!"