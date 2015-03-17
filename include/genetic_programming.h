#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifndef _GENETIC_PROGRAMMING_H_
#define _GENETIC_PROGRAMMING_H_


const int POP = 1000;
const int GEN = 1000;
struct bin_tree
{
    char value;
    short int depth;
    bin_tree *left_child;
    bin_tree *right_child;
};


void genetic_programming();
//initialize population
void initpop( struct bin_tree *trees );
void rec_init( struct bin_tree *parent, short int depth, short int num_children );
//Randomly generates value stored in node
char generate_terminal();
char generate_operator();
//Genetic operators
void recomb( struct bin_tree *tree_1, struct bin_tree *tree_2, struct bin_tree *new_tree );
void recursive_recomb( char spot, struct bin_tree* tree, struct bin_tree* new_tree);
void recomb_copy(struct bin_tree *tree, struct bin_tree *new_tree, int depth );
void recursive_mutate( char spot, struct bin_tree* tree );
void mutate_node( struct bin_tree *tree );
//Calculates the fitness of the trees
void fitness(struct bin_tree *trees, bool correct[][21], double fit[] );
bool check_answer( int x_val, int answer);
double calc_fit( bool correct[]);
int evaluate_tree( struct bin_tree *tree, int x_val);
int terminal_to_int( char term, int x_val);
//print pop
void print_pop( struct bin_tree *trees, double fit_vals[] );
void print_tree( struct bin_tree *tree);
void sort_trees( struct bin_tree *trees, double fit_vals[]);
void clear_tree( struct bin_tree *tree);
void swap_subtrees( struct bin_tree *tree1, struct bin_tree *tree2);

#endif
