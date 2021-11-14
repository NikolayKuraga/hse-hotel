CC=g++
CFLAGS=-g -Wall -Wfatal-errors

all: main.run

client.o: client.cpp client.hpp
	$(CC) $(CFLAGS) -c client.cpp `wx-config --cxxflags` -o client.o

main.run: main.cpp client.o
	$(CC) $(CFLAGS) main.cpp client.o `wx-config --cxxflags --libs` -o main.run

clean:
	rm client.o main.run
