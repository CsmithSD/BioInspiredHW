#include "../include/ant_colony_optimization.h"
#include "../include/simulated_annealing.h"


int S_ACO(const char* map, int population)
{
    vector<pos> graph;
    vector<int> best;
    vector<vector<double> > edge;
    vector<vector<double> > vis;
    vector<vector<double> > phe;
    vector<vector<int> > ants;
    unsigned int n;     //used for number of cities 

    //Load graph (map of cities) and check 
    n = load_cities(map, graph);
    if(n < 0)
    {
        printf("Error loading cities\n");
        return n;
    }

    //initialize the map of all edges
    init_edges(edge, graph, n);
    
    //Initialize Best (ordered cities)
    best.resize(n);
    for(int i = 0; i < n; i++)
        best[i] = i;

    //Initialize visibility
    init_visibility(vis, edge);

    //Initialize pheromone trail
    phe = vis;

    //Initialize population of ants
    init_population(ants, edge, population);


    //Loop for maximum number of iterations

        //Loop for each ant

            //Loop for an ant to visit each city only once

                //Proababilistic transition rule
                //determines the probability of an ant choosing an edge
                //and then choosing a specifyed edge

            //end for
        //end for

        //Loop to find the cost of every solution built

            //if improvment, set to best

        //update pheromone trails

    return 0;
}


//takes a file and loads cities into a vector called graph
int load_cities(const char* fileName, vector<pos> &graph)
{
    FILE* fin = fopen(fileName, "r");
    char buffer[50];
    pos city;

    graph.resize(0);

    if(fin == NULL)
    {
        printf("Could not open file\n");
        return -1;
    }


    while( fgets(buffer, 50, fin) != NULL )
    {
        //extract city position from file
        city.x = atof(buffer);
        city.y = atof(strchr(buffer, ' ') );

        //insert city into graph
        graph.push_back(city);
    }

    return (int) graph.size();
}

//populates edges vector with lengths of edges
void init_edges(vector<vector<double> > &edge, vector<pos> &graph, unsigned int numCities)
{
//    unsigned int e;     //used for number of edges
    double xsquared;
    double ysquared;


//    e = (double)numCities * (double)(numCities-1) / 2.0;
//    edge.resize(e);

    edge.resize(numCities);

    //find the distances from each city to another
    for(unsigned int startCity = 0; startCity < numCities; startCity++)
    {
        edge[startCity].resize(numCities);
        for(unsigned int endCity = 0; endCity < numCities; endCity++)
        {
            xsquared = pow( graph[startCity].x - graph[endCity].x, 2 );
            ysquared = pow( graph[startCity].y - graph[endCity].y, 2 );
            edge[startCity][endCity] = pow( xsquared + ysquared, 0.5 );
        }
    }

}

void init_visibility(vector<vector<double> > &vis, vector<vector<double> > &edge)
{
    vis = edge;

    //the visibility from one city to another is inversly
    //proportional to the distance between the two cities
    for(unsigned int startCity = 0; startCity < edge.size(); startCity++)
    {
        for(unsigned int endCity = 0; endCity < edge.size(); endCity++)
        {
            vis[startCity][endCity] = 1.0 / edge[startCity][endCity];
        }
    }
}

void init_population(vector<vector<int> > ants, vector<vector<double> > edges, int population)
{
    cout << population << endl;
    int e = random(0, population-1);

    cout << e << endl;
}
