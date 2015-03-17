#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "fit_func.h"
#ifndef _PARTICLE_SWARM_H_
#define _PARTICLE_SWARM_H_



#define SWARM_POP 20
#define SWARM_STEPS 200
#define SWARM_GENS 500
void particle_swarm();

void init_swarm( double swarm[]);
void init_vel( double vel[] );
void init( double swarm[], double best_ind[], double fit_best[]);

double fit_swarm(double swarm[], double fitness[] );

void print_swarm( double swarm[], double fitness[]);
double print_vel( double vel[] );
#endif
