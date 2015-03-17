#include <math.h>
#include "fit_func.h"
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <string.h>
#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_


const int GEN = 5000;
const int SIZE = 11;
const int BITS = 10;
const int POP = 100;


void genetic_algorithm();
void mutate( char *string );
void recomb( char *string1, char *string2, char *string3);
void initpop( char population[][SIZE] );
void printpop( char population[][SIZE], double fitness[]);
double encode( char* string );
int bin2dec( char *string );
void decode( double value, char *string);
void dec2bin( int val, char *string);
void fitpop( char population[][SIZE], double fitness[]);
void sort( char population[][SIZE], double fitness[] );

#endif
