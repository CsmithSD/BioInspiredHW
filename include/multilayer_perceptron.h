#ifndef _MULTILAYER_PERCEPTRON_H_
#define _MULTILAYER_PERCEPTRON_H_

#include <stdio.h>  //printf
#include <cstdlib>  //File IO
#include <vector>
#include <string.h>
#include <new>      //dynamic memory allocation
#include <iostream>
#include <math.h>
#include <limits.h> //INT_MAX

using namespace std;


int extract_pattern(const char* inputFile, int patterns[][120]);
int multilayer_perceptron(const char* inputFile);
void load_pattern(vector<double> &neurons, int* pattern);
void init_neurons( vector<vector<double> > &neurons, int layers);
void init_weights( vector<vector<vector<double> > > &weights, int layers);
void check_weights(vector<vector<vector<double> > > &weights);
void check_neurons(vector<vector<double> > &neurons);
void check_deltas(vector<vector<double> > &deltas);
void adjust_weights(vector<vector<vector<double> > > &weights, vector<vector<double> > &neurons, vector<vector<double> > &deltas, double learningRate);
void feed_forward(vector<vector<double> > &neurons, vector<vector<vector<double> > > &weights);
double find_deltas(vector<vector<double> > &deltas, vector<vector<double> > &neurons, vector<vector<vector<double> > > & weights, vector<double> &desired);
void init_deltas( vector<vector<double> > &deltas, int layers);
void init_desired(vector<vector<double> > &desired, int* desiredOut);
inline double activation_function(double x);

#endif
