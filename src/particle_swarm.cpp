#include "../include/particle_swarm.h"

int main()
{
    particle_swarm();
    return 0;
}
//Basic outline taken from slides for csc 492 with slight modifications to fit current problem
void particle_swarm()
{
    int i, j = 0;
    double swarm[SWARM_POP],
           vel[SWARM_POP],
           best_ind[SWARM_POP], 
           fitness[SWARM_POP], 
           fit_best[SWARM_POP];
    double best, top, phi1, phi2;

    srand( time(NULL));
    init_swarm(swarm);
    best = fit_swarm(swarm , fitness);
    top = fit(best);
    print_swarm(swarm, fitness);
    while( j++ < SWARM_GENS )
    {
        for( i = 0; i < SWARM_POP; i++ )
        {
            phi1 = rand()%SWARM_STEPS/1000.0 - 0.1;
            phi2 = rand()%SWARM_STEPS/1000.0 - 0.1;
            vel[i] += phi1 * ( best_ind[i] - swarm[i] ) + phi2 * ( best - swarm[i] );
            if(( swarm[i] + vel[i] > 0.0 ) && ( swarm[i] + vel[i] < 1.0 ))
            {
                swarm[i] += vel[i];
                fitness[i] = fit( swarm[i] );

            }
        }
        for( i = 0; i< SWARM_POP; i++)
        {
            if( fitness[i] > fit_best[i])
            {
                best_ind[i] = swarm[i];
                fit_best[i] = fitness[i];
            }
            if( fitness[i] > top)
            {
                best = swarm[i];
                top = fitness[i];
            }
        }
    }
    printf( "Best is %f\n", best);
}

void init_swarm( double swarm[])
{
   for( int i = 0; i < SWARM_POP; i++ )
   {
        swarm[i] = ((double)rand())/RAND_MAX;
   }
}

void init_vel( double vel[] )
{
    for( int i = 0; i < SWARM_POP; i++ )
        vel[i] = ((double)rand()) / RAND_MAX * ( ( rand()&1 ) ? 1 : -1 );
}

void init( double swarm[], double best_ind[], double fit_best[])
{

}

double fit_swarm( double swarm[], double fitness[] )
{
    double best = 0;
    for( int i = 0; i < SWARM_POP; i++ )
    {
        fitness[i] = fit( swarm[i] );
        if(fitness[i] > best )
            best = fitness[i];
    }
    return best;
}

void print_swarm( double swarm[], double fitness[])
{
    for( int i = 0; i < SWARM_POP; i++)
        printf("individual: %f fitness: %f\n", swarm[i], fitness[i]);
}

double print_vel( double vel[] )
{
    return 1.0;
}

void sort_swarm( double swarm[], double fitness[] )
{

}











