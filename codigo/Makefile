CPPFLAGS=--std=c++11 
CC = g++

all: nsp.o nursescheduling.o helpers.o assignment.o 
	$(CC) assignment.o helpers.o nursescheduling.o nsp.o -o nsp

nsp.o: nsp.cpp nursescheduling.hpp helpers.hpp assignment.hpp
	$(CC) $(CPPFLAGS) -c nsp.cpp

nursescheduling.o: nursescheduling.cpp
	$(CC) $(CPPFLAGS) -c nursescheduling.cpp

helpers.o: helpers.cpp
	$(CC) $(CPPFLAGS) -c helpers.cpp
assignment.o: assignment.cpp
	$(CC) $(CPPFLAGS) -c assignment.cpp

binaries: assignment.o helpers.o nursescheduling.o nsp.o 

clean:
	rm -f $(binaries) *.o nsp


