#include "../include/simulated_annealing.h"


double pertubation( double individual)
{

    return random(0,1);

}

inline double random( double min, double max)
{
    return ((double)rand()/(double)RAND_MAX)*(max-min);
}
