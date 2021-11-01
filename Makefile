CC=g++
CFLAGS=-g -Wall -Wfatal-errors

all: server.run client.run

shared.o: shared.cpp shared.hpp
	$(CC) $(CFLAGS) -c shared.cpp -o shared.o

server.run: shared.o server.cpp server.hpp shared.hpp
	$(CC) $(CFLAGS) server.cpp shared.o -o server.run

client.run: shared.o client.cpp client.hpp shared.hpp
	$(CC) $(CFLAGS) client.cpp shared.o `wx-config --cxxflags --libs` -o client.run

clean:
	rm shared.o client.run server.run
