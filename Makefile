CC=g++
CFLAGS=-g -Wall -Wfatal-errors

all: server.run client.run

server.run: server.cpp server.hpp shared.hpp
	$(CC) $(CFLAGS) server.cpp -o server.run

client.run: client.cpp client.hpp shared.hpp
	$(CC) $(CFLAGS) `wx-config --cxxflags --libs` client.cpp -o client.run

clean:
	rm -rf *.o *.run
