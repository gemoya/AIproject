CPPFLAGS=--std=c++11 -Wall
CC = g++

all: nsp.o nursescheduling.o helpers.o
	$(CC) helpers.o nursescheduling.o nsp.o -o nsp

nsp.o: nsp.cpp nursescheduling.hpp helpers.hpp
	$(CC) $(CPPFLAGS) -c nsp.cpp

nursescheduling.o: nursescheduling.cpp
	$(CC) $(CPPFLAGS) -c nursescheduling.cpp

helpers.o: helpers.cpp
	$(CC) $(CPPFLAGS) -c helpers.cpp
