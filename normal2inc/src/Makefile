all:normal2inc
CFLAGS= -static
normal2inc: main.cpp normal2inc.o
	g++ ${CFLAGS} -o $@ $^

normal2inc.o: normal2inc.cpp
	g++ ${CFLAGS} -c -o $@ $<
