#ifndef _ANT_COLONY_OPTIMIZATION_H_
#define _ANT_COLONY_OPTIMIZATION_H_

#include "../include/simulated_annealing.h"
#include <stdio.h>  //printf
#include <cstdlib>  //File IO
#include <vector>
#include <string.h>
#include <iostream>
#include <math.h>
#include <limits.h> //INT_MAX
#include <float.h> //DBL_MAX

using namespace std;

struct pos
{
    double x;
    double y;
};

int S_ACO(const char* map, int population);
int load_cities(const char* fileName, vector<pos> &graph);
int init_edges(vector<double> &edges, vector<pos> &graph, vector<vector<int> > &map, unsigned int numCities);
void init_visibility(vector<double> &vis, vector<double> &edges);
void init_pop(vector<vector<int> > &ants, int pop, int numCities);
void update_pop(vector<vector<int> > &ants);
bool choose_path(vector<int> &ant, vector<double> &edges, vector<vector<int> > &map, vector<double> &phe, vector<double> &vis, int numCities);
void update_visited(vector<bool> &visited, vector<int> &ant);
void find_best(vector<vector<int> > &ants, vector<double> edges, vector<vector<int> > &map, vector<int> &bestPath, double &best);
void update_pheromone(vector<vector<int> > &ants, vector<double> &phe, vector<vector<int> > &map, double decayRate);
int contains(vector<int> &vec, int item);
int contains(vector<bool> &vec, bool item);


#endif
