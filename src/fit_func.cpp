#include "../include/fit_func.h"

double fit( const double &x )
{
    return pow(2, -2 * ( (x - 0.1 / 0.9) * (x - 0.1 / 0.9 ) ) ) * pow(sin(5*M_PI*x), 6);
}
