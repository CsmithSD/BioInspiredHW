#ifndef _HILL_CLIMBING_H_
#define _HILL_CLIMBING_H_

#define SIZE 100
void hill_climbing();
void hill_fit( double x );
void hill_sort( double pop[], double fitness[]);
void hill_init_pop( double pop[]);
void hill_printpop( double pop[], double fitness[] );
void hill_fit_pop( double pop[], double fitness[] );

#endif
