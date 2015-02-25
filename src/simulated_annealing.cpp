//#include <boost/random.hpp>
#include <cstdlib>
#include <iostream>
#include "../include/fit_func.h"

#define GEN 500

//function prototypes 
double pertubation( double individual);
double random( double min, double max);
void initialize_T(double & t);
void update(double & T);

using namespace std;

int main()
{
    //Seed random number generator
    srand(time(NULL));

    //initialize individual inbetween -1 and 1 
    double x = random(-1, 1);
    double xprime;      //next pertubation of individual
    double T = 1.0;     //initialize T (temperature) at a higher value

    //Loop though the number of generations
    for(int i = 0; i < GEN; i++)
    {
        //pertubation of the individual
        xprime = pertubation(x);

        //evaluation of the individuals using T
        if( random(0, 1) < exp( (fit(xprime) - fit(x))/T ) )
        {
            cout << i << ": " << fit(xprime) - fit(x) << endl;
            x = xprime;
        }
        
        update(T);
    }

    cout << x << " : " << fit(x) << endl;
    
    return 0;
}


double pertubation( double individual)
{
    return individual + random(-.2, .2);
}

inline double random( double min, double max)
{
    return ((double)rand()/(double)RAND_MAX)*(max-min) + min;
}

void initialize_T(double & t)
{
    t = 1.00;
}

void update(double & t)
{
    t = ( t* (.95) );
}
