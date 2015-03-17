#include "../include/hill_climbing.h"

int main()
{
    int input;
    printf("Enter number of points to run hill climbing algorithm on: ");
    scanf("%d", &input );
    hill_climbing( input );
    return 0;
}

void hill_climbing( const int &num_points )
{
    int k = 0;
    int i = 0;
    double *x = (double*) malloc( sizeof(double) * num_points);
    double *x_prime = (double*) malloc(sizeof(double)*num_points);
    double best = 0;

    bool *local_optima_found = (bool*) malloc( sizeof(bool) * num_points );
    srand(time(NULL));

    printf("Starting point(s):\n");
    //initialize individual(s) inbetween 0 and 1
    for( i = 0; i < num_points; i++)
    {
        x[i] = random(0.0,1.0);
        local_optima_found[i] = false;
        printf("\t%f\n", x[i]);
    }

    best = x[0];
    printf("\n\n");
    while( k < kmax)
    {
        for(i = 0; i < num_points; i++)
        {
            double perturb = 0.01 ;
            x_prime[i] = x[i] + perturb;
            if( !local_optima_found[i] && fit( x_prime[i] ) > fit(x[i]) )
            {
                x[i] = x_prime[i];
                //Storing best so far if x_prime is better than best
                if( fit(x[i]) > fit(best) )
                    best = x[i];
            }
            else if( !local_optima_found[i] && fit(x_prime[i]-perturb*2) > fit( x[i] ) )
            {
                x[i] = x_prime[i] - perturb*2;
                //Storing best so far if x_prime is better than best
                if( fit(x[i]) > fit(best) )
                    best = x[i];
            }
            else
                local_optima_found[i] = true;
        }
        printf("Best so far: %f\n\n", best);
        k++;
    }
    printf("Overall optima found: %f\n", best);
    
    free(x);
    free(x_prime);
    free(local_optima_found);
}


double random( double min, double max)
{
    return ((double)rand()/(double)RAND_MAX)*(max-min) + min;
}


