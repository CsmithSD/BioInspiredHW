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
CFLAGS = -finline-functions -g -O3 -Wall
CXXFLAGS = -finline-functions -g -O3 -Wall

VPATH = src
#-----------------------------------------------------------------------

# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:    hill_climbing stochastic_hill simulated_annealing genetic_algorithm genetic_programming particle_swarm bone_marrow ant_colony_optimization

# specific targets
hill_climbing: hill_climbing.o fit_func.o
	$(LINK) $(CFLAGS) $^ -o $@
stochastic_hill: stochastic_hill_climbing.o fit_func.o
	$(LINK) $(CFLAGS) $^ -o $@
simulated_annealing: simulated_annealing.o fit_func.o
	$(LINK) $(CFLAGS) $^ -o $@
genetic_algorithm: genetic_algorithm.o fit_func.o
	$(LINK) $(CFLAGS) $^ -o $@
genetic_programming: genetic_programming.o
	$(LINK) $(CFLAGS) $^ -o $@
particle_swarm: particle_swarm.o fit_func.o
	$(LINK) $(CFLAGS) $^ -o $@
bone_marrow: bone_marrow.o
	$(LINK) $(CFLAGS) $^ -o $@
ant_colony_optimization: ant_colony_optimization.o 
	$(LINK) $(CFLAGS) $^ -o $@

#bio_inspired_hw:	main.o bone_marrow.o hill_climbing.o  fit_func.o particle_swarm.o simulated_annealing.o genetic_programming.o
#	$(LINK) -g -Wall -o $@ $^

# generic C and C++ targets for OpenGL programs consisting of only one file
# type "make filename" (no extension) to build
.c:
	$(CC) $(CFLAGS) -o $@ $@.c $(GL_LIBS)

.cpp:
	$(CXX) $(CFLAGS) -o $@ $@.cpp $(GL_LIBS)

# utility targets
clean_objects:
	rm -f *.o *~ core
clean_execs:
	rm -f hill_climbing stochastic_hill simulated_annealing genetic_algorithm genetic_programming particle_swarm bone_marrow ant_colony_optimization
clean:
	rm -f *.o *~ core
	rm -f hill_climbing stochastic_hill simulated_annealing genetic_algorithm genetic_programming particle_swarm bone_marrow ant_colony_optimization
