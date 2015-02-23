# Makefile for OpenGL/GLUT programs.

# Author: John M. Weiss, Ph.D.
# Written Fall 2014 for CSC433/533 Computer Graphics.

# Usage:  make target1 target2 ...

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = g++

# Turn on optimization and warnings (add -g for debugging with gdb):
# CPPFLAGS = 		# preprocessor flags
CFLAGS = -g -O -Wall
CXXFLAGS = -g -O -Wall

VPATH = src
#-----------------------------------------------------------------------

# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:    bio_inspired_hw

# specific targets
bio_inspired_hw:	main.o simulated_annealing.o hill_climbing.o genetic_algorithm.o fit_func.o
	$(LINK) -I/usr/include/boost-1_33 -L/usr/lib -o $@ $^

# generic C and C++ targets for OpenGL programs consisting of only one file
# type "make filename" (no extension) to build
.c:
	$(CC) -o $@ $@.c $(GL_LIBS)

.cpp:
	$(CXX) -o $@ $@.cpp $(GL_LIBS)

# utility targets
clean:
	rm -f *.o *~ core
