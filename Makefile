CC=g++
CFLAGS=-g -Wall -Wfatal-errors

all: server client

shared.o: shared.cpp shared.hpp
	$(CC) $(CFLAGS) -c shared.cpp

server.o: server.cpp server.hpp shared.hpp
	$(CC) $(CFLAGS) -c server.cpp

client.o: client.cpp client.hpp shared.hpp
	$(CC) $(CFLAGS) -c client.cpp

server.run server: server.o shared.o
	$(CC) $(CFLAGS) server.o shared.o -o server.run

client.run client: client.o shared.o
	$(CC) $(CFLAGS) client.o shared.o -o client.run

clean:
	rm -rf *.o *.run
