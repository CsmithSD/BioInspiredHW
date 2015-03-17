#ifndef _SIMULATED_ANNEALING_H_
#define _SIMULATED_ANNEALING_H_

#include <cstdlib>
#include <iostream>

double pertubation( double individual);
inline double random( double min, double max);
void initialize_T(double & t);
void update(double & T);
int simulated_annealing();
int stochastic_hill_climbing();

inline double random( double min, double max)
{
    return ((double)rand()/(double)RAND_MAX)*(max-min) + min;
}

#endif
