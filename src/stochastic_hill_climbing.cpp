#include "../include/fit_func.h"
#include "../include/simulated_annealing.h"

#define GEN 500

//function prototypes 

using namespace std;

int main()
{
    stochastic_hill_climbing();
    
    return 0;
}

int stochastic_hill_climbing()
{
    double T = .05;
    //Seed random number generator
    srand(time(NULL));

    //initialize individual inbetween -1 and 1 
    double x = random(-1, 1);
    double xprime;      //next pertubation of individual

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
    }

    cout << x << " : " << fit(x) << endl;
    
    return 0;
}


double pertubation( double individual)
{
        return individual + random(-.2, .2);
}

void initialize_T(double & t)
{
        t = 1.00;
}




