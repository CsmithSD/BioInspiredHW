#include "../include/hill_climbing.h"


void hill_climbing()
{
    uniform_01<mpf_float_50> uf;
    independent_bits_engine<mt19937, 50L*1000L/301L, mpz_int> gen;
    
    std::cout << uf(gen) << std::endl;
    
    int k = 0;
    double x;
    double x_prime;
    bool improvement = true;
    while( k < kmax)
    {
        x_prime = x + ( uf(gen) < 0.5 ) ? (-0.01) : 0.01;
        if( fit_func( x_prime) > fit_func(x) )
            x = x_prime;
        k++;
    }
}
