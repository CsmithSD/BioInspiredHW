#include "fit_func.h"

#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>

using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;

#ifndef _HILL_CLIMBING_H_
#define _HILL_CLIMBING_H_

#define kmax 100
void hill_climbing();
double hill_pert( const double &x );
#endif
