CC=g++
CFLAGS=-g -Wall -Wfatal-errors

all: server.run client.run

shared.o: shared.cpp shared.hpp
	$(CC) $(CFLAGS) -std=gnu++17 -c shared.cpp -o shared.o

server.run: shared.o server.cpp server.hpp shared.hpp
	$(CC) $(CFLAGS) -std=gnu++11 server.cpp shared.o -pthread -o server.run

client.run: shared.o client.cpp client.hpp shared.hpp
	$(CC) $(CFLAGS) -std=gnu++11 client.cpp shared.o `wx-config --cxxflags --libs` -o client.run

clean:
	rm -f shared.o client.run server.run
