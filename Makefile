CC=g++
CFLAGS=-g -Wall -Wfatal-errors -std=c++11 -DPQXX_HIDE_EXP_OPTIONAL

all: main.run

dbi.o: dbi.hpp dbi.cpp
	$(CC) $(CFLAGS) -c dbi.cpp -o dbi.o

gui.o: gui.hpp gui.cpp
	$(CC) $(CFLAGS) -c gui.cpp `wx-config --cxxflags` -o gui.o

main.run: dbi.o gui.o main.cpp
	$(CC) $(CFLAGS) gui.o dbi.o main.cpp -lpqxx -lpq `wx-config --cxxflags --libs std,richtext` -o main.run

clean:
	rm -Rf gui.o dbi.o main.run
