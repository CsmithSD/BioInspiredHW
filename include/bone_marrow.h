#include <stdio.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <math.h>
#ifndef _BONE_MARROW_H_
#define _BONE_MARROW_H_

struct city
{
    int x;
    int y;
};
#define N_CITIES 32
#define N_LIBRARIES 8
#define GENE_LENGTH 4
#define NUM_GENES 8
#define BONE_POP 10000
#define BONE_GENS 1000

void bone_marrow();
void init_cities( struct city cities[] );
void init_libraries( int libraries[][NUM_GENES][GENE_LENGTH] );
void init_pop( int population[][N_CITIES], int libraries[][NUM_GENES][GENE_LENGTH] );
void check_repeats( int population[] );
void eval_pop( int population[][N_CITIES], double fitness[], struct city cities[]);
void print_pop( int population[], double fitness);
double calc_fit( int population[], struct city cities[]);
void sort_pop(int population[][N_CITIES], double fitness[]);
void stack_encoding_mutate( int individual[] );
void stack_encoding_recomb( int left[], int right[], int new_ind[] );



#endif
