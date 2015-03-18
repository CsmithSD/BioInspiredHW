#include "../include/ant_colony_optimization.h"

#define MAX_IT 100

int main()
{
    S_ACO("cities.txt", 10);

    return 0;
}

int S_ACO(const char* file, int population)
{
    vector<pos> graph;
    vector<int> bestPath;
    vector<double> edges;
    vector<double> vis;
    vector<double> phe;
    vector<vector<int> > ants;
    vector<vector<int> > map;
    int numCities;               //used for number of cities 
    double best = DBL_MAX;
    double pheDecay = .7;    //pheromone decay rate
    
    //Load graph (map of cities) and check 
    numCities = load_cities(file, graph);
    if(numCities < 0)
    {
        printf("Error loading cities\n");
        return numCities;
    }

    //seed random number generator
    srand(time(NULL));

    //initialize the map of all edges
   init_edges(edges, graph, map, numCities);
    
    //Initialize Best (ordered cities)
    bestPath.resize(numCities);
    for(int i = 0; i < numCities; i++)
        bestPath[i] = i;

    //Initialize visibility
    init_visibility(vis, edges);

    //Initialize pheromone trail
    phe = vis;

    //Initialize population of ants
    init_pop(ants, population, numCities);


//    double pathLength = 0;
//    int prev;
//    int curr;
//    int ans[32] = {2, 18, 10, 6, 1, 17, 24, 21, 9, 15, 14, 5, 8, 0, 7, 12, 13, 16, 31, 25, 22, 29, 28, 27, 23, 30, 26, 19, 20, 11, 4, 3};
//
//    //calculate the path traveled by each ant and compare with the best
//    for(unsigned int city = 1; city < 32; city++)
//    {
//        prev = ans[city-1];
//        curr = ans[city];
//        //map has to index with smalles value first
//        if(  prev < curr )
//            pathLength += edges[map[prev][curr - (prev+1)]];
//        else
//            pathLength += edges[map[curr][prev - (curr+1)]];
//    }


    //Loop for maximum number of iterations
    for(int i = 0; i < MAX_IT; i++)
    {
        //run one iteration of ants to solve TSP
        for(unsigned int tsp = 0; tsp < (unsigned int)(numCities-1); tsp++)
        {
            //Loop for each ant
            for(unsigned int ant = 0; ant < ants.size(); ant++)
            {
                //individual ant picks edge based on the 
                //probabilistic transition rule
                choose_path(ants[ant], edges, map, phe, vis, numCities);
            }

            //update pheromone trails
            update_pheromone(ants, phe, map, pheDecay);
        }

        //Loop to find the cost of every solution built
        //and find the best
        find_best(ants, edges, map, bestPath, best);


        //update ants vector
        ants.clear();
        init_pop(ants, population, numCities);
    }

    printf("Best Path: ");
    for(unsigned int i = 0; i < bestPath.size(); i++)
     {
        printf("%d ", bestPath[i]);
     }
    printf(" Distance: %f\n", best);

    return 0;
}


void update_pheromone(vector<vector<int> > &ants, vector<double> &phe, vector<vector<int> > &map, double decayRate)
{
    int prev;
    int curr;
    double pindex;

    for(unsigned int ant = 0; ant < ants.size(); ant++)
    {
        prev = ants[ant][ants[ant].size()-2];
        curr = ants[ant].back();

        //get the pheramone from the paths the ants just travled
        if(  prev < curr )
            pindex = map[prev][curr - (prev+1)];
        else
            pindex = map[curr][prev - (curr+1)];

        //update the pheromone using the decay rate
        phe[pindex] = (1-decayRate)*phe[pindex] + 1;
    }
}

void find_best(vector<vector<int> > &ants, vector<double> edges, vector<vector<int> > &map, vector<int> &bestPath, double &best)
{
    double pathLength = 0;
    int prev;
    int curr;

    for(unsigned int ant = 0; ant < ants.size(); ant++)
    {
        //calculate the path traveled by each ant and compare with the best
        for(unsigned int city = 1; city < ants[ant].size(); city++)
        {
            prev = ants[ant][city-1];
            curr = ants[ant][city];
            //map has to index with smalles value first
            if(  prev < curr )
                pathLength += edges[map[prev][curr - (prev+1)]];
            else
                pathLength += edges[map[curr][prev - (curr+1)]];
        }

        //keep records of the best path lenght
        if(pathLength < best)
        {
            best = pathLength;
            bestPath = ants[ant];
        }

        pathLength = 0;
    }
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
//returns number of edges
int init_edges(vector<double> &edges, vector<pos> &graph, vector<vector<int> > &map, unsigned int numCities)
{
    unsigned int e;     //used for number of edges
    double xsquared;
    double ysquared;
    int path = 0;

    //initialize the number of edges
    e = (unsigned int)(numCities * (double)(numCities-1) / 2.0);
    edges.resize(e);
    map.resize(numCities-1);

    //find the distances from each city to another
    for(unsigned int startCity = 0; startCity < numCities; startCity++)
    {
        for(unsigned int endCity = startCity; endCity < numCities; endCity++)
        {
            if(startCity == endCity)
                continue;
            xsquared = pow( graph[startCity].x - graph[endCity].x, 2 );
            ysquared = pow( graph[startCity].y - graph[endCity].y, 2 );
            edges[path] = sqrt( xsquared + ysquared );

            map[startCity].push_back(path);

            path++;
        }
    }

    return path;
}

void init_visibility(vector<double> &vis, vector<double> &edges)
{
    vis = edges;

    //the visibility from one city to another is inversly
    //proportional to the distance between the two cities
    for(unsigned int edge = 0; edge < edges.size(); edge++)
        vis[edge] = 1.0 / edges[edge];
}

void init_pop(vector<vector<int> > &ants, int pop, int numCities)
{
    ants.resize(pop);

    for(int i = 0; i < pop; i++)
    {
        ants[i].push_back( (int) random(0, numCities) );
    }
}

void update_pop(vector<vector<int> > &ants)
{
    int temp;
    
    for(unsigned int ant = 0; ant < ants.size(); ant++)
    {
        temp = ants[ant].back();
        ants.clear();
        ants[ant].push_back(temp);
    }
}


bool choose_path(vector<int> &ant, vector<double> &edges, vector<vector<int> > &map, vector<double> &phe, vector<double> &vis, int numCities)
{
    int prevCity = ant.back();
    int city = -1;
    int path;
    int index;
    double choice;
    double alpha = 1.0;
    double beta = 1.0;
    double total = 0.0;
    vector<double> prob;
    vector<int> options;
    vector<bool> visited(numCities, false);

    //check in case ant has already traveld to all cities
    if(ant.size() >= (unsigned int)numCities)
        return false;

    //make sure ant doesn't visit cities that it has already been to
    update_visited(visited, ant);

    //find all probabilities of remaning paths
    while( (city = contains(visited, false)) != -1 )
    {
        //find index into the city
        if(prevCity < city)
            path = map[prevCity][city - (prevCity+1)];
        else
            path = map[city][prevCity - (city+1)];

        //save city as an option to choose from
        options.push_back(city);

        //find the accumulative probability of ant choosing a path
        prob.push_back( (pow(phe[path], alpha)*pow(vis[path], beta )) + total);
        total += prob.back();

        visited[city] = true;
    }

    //total is actually equal to the last element of the accumulative prob
    total = prob.back();

    //choose a path
    choice = random(0, total);
    for(index = 0; choice > prob[index]; index++);

    //insert next city choice into path
    ant.push_back(options[index]);

    return true;
}

void update_visited(vector<bool> &visited, vector<int> &ant)
{
    for(unsigned int city = 0; city < ant.size(); city++)
        visited[ant[city]] = true;
}

int contains(vector<bool> &vec, bool item)
{
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == item)
            return i;
    }

    return -1;
}

int contains(vector<int> &vec, int item)
{
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == item)
            return i;
    }

    return -1;
}
