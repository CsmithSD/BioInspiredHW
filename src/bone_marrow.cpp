#include "../include/bone_marrow.h"


int main()
{
    bone_marrow();
    return 0;
}

void bone_marrow()
{
    srand(time(NULL));
    struct city cities[N_CITIES];
    int libraries[N_LIBRARIES][NUM_GENES][GENE_LENGTH];
    int population[BONE_POP][N_CITIES];
    double fitness[BONE_POP];
    //bone marrow initialisation
    int i, j, mom, dad; 
    init_libraries( libraries );
    init_cities( cities );
    init_pop( population, libraries );
    eval_pop( population, fitness, cities ) ;
    
    sort_pop( population, fitness);
    for( i = 0; i < BONE_GENS; i++ )
    {
        for( j = BONE_POP/2; j < BONE_POP; j++)
        {
            mom = rand() % ( BONE_POP / 2 );
            dad = rand() % ( BONE_POP / 2 );
            stack_encoding_recomb( population[mom], population[dad], population[j] );
            stack_encoding_mutate( population[j] );
            fitness[j] = calc_fit( population[j], cities);
        }
        sort_pop( population, fitness);
    }
    print_pop( population[0], fitness[0] );
}

void print_pop( int population[], double fitness )
{
    int i, j, k;
    bool city_used[N_CITIES] = { false };
    int city_index;
    printf( "Shortest Path Found:" );
    for( i = 0; i < N_CITIES; i++ )
    {
        city_index = population[i];
        j = -1;
        k = 0;
        while( j < city_index )
        {
            while( city_used[k] )
                k++;
            j++;
            if( j != city_index )
                k++;
        }
        city_used[k] = true;
        printf( " %d", k );
    }
    printf( " Distance: %f\n", fitness );
}


void init_cities( struct city cities[] )
{
    std::ifstream fin;
    fin.open("cities.txt");
    for( int i = 0; i < N_CITIES; i++ )
    {
        fin >> cities[i].x;
        fin >> cities[i].y;
    }
    fin.close();
}

void init_libraries( int libraries[][NUM_GENES][GENE_LENGTH] )
{
    int i, j, k;
    for( i = 0; i < N_LIBRARIES; i++ )
        for( j = 0; j < NUM_GENES; j++ )
            for( k = 0; k < GENE_LENGTH; k++ )
            {
                    libraries[i][j][k] = rand() % ( N_CITIES - (k + ( GENE_LENGTH * i)) );
            }
}

void init_pop( int population[][N_CITIES], int libraries[][NUM_GENES][GENE_LENGTH] )
{
    int i, j, k, l;
    int m;
    for( i = 0; i < BONE_POP; i++)
    { 
        m = 0;
        for( k = 0; k < N_LIBRARIES; k++ )
        {
            j = rand() % NUM_GENES;
            for( l = 0; l < GENE_LENGTH; l++)
            {
                population[i][m] = libraries[k][j][l];
                m++;
            }
        }
    }
}

void eval_pop( int population[][N_CITIES], double fitness[], struct city cities[] )
{
    for( int i = 0; i < BONE_POP; i++)
    {
        fitness[i] = calc_fit( population[i], cities );
    }
}

double calc_fit( int population[], struct city cities[] )
{
    double distance = 0.0;
    double delta_x = 0;
    double delta_y = 0;
    int i ,j, k;
    bool city_used[N_CITIES] = { false };
    int city_index;
    for( i = 0; i < N_CITIES; i++ )
        city_used[i] = false;
    for( i = 0; i < N_CITIES-1; i++ )
    {
        //undoes the stack encoding for a city
        city_index = population[i];
        j = -1;
        k = 0;
        //sets k to the first available city
        while( j < city_index )
        {
            while(city_used[k])
                k++;
            j++;
            if( j != city_index)
                k++;
        }
        city_used[k] = true;
        //store the city x and y coordinates   
        delta_x = cities[k].x;
        delta_y = cities[k].y;

        //undoes the stack encoding for a city
        city_index = population[ i+1 ];
        k = 0;
        j = -1;
        while( j < city_index )
        {
            while( city_used[k] )
                k++;
            j++;
            if( j != city_index )
                k++;
        }
        //distance formula is used
        delta_x -= cities[k].x;
        delta_y -= cities[k].y;
        
        delta_x *= delta_x;
        delta_y *= delta_y;
        
        distance += sqrt( delta_x + delta_y );  
    }
    return distance;     
    printf("SHOULD NOT HIT\n");
}

void sort_pop(int population[][N_CITIES], double fitness[] )
{
   bool swapped = true;
   double tmp;
   int j = 0;
   int pop_tmp;

   while( swapped )
   {
       swapped = false;
       j++;
       for( int i = BONE_POP - 1; i > 0; i-- )
       {
           if( fitness[i] < fitness[i-1] )
           {
               tmp = fitness[i];
               fitness[i] = fitness[i-1];
               fitness[i-1] = tmp;
               swapped = true;
               for( j = 0; j < N_CITIES; j++)
               {
                   pop_tmp = population[i][j];
                   population[i][j] = population[i-1][j];
                   population[i-1][j] = pop_tmp;
               }
           }
       }
   }
}

void stack_encoding_mutate( int individual[] )
{
    int spot = rand() % N_CITIES;
    int x = individual[spot];
    while (x == individual[spot] && spot != (N_CITIES -1) )
        individual[spot] = rand() % ( N_CITIES - spot );
}

void stack_encoding_recomb( int left[], int right[], int new_ind[] )
{
    int spot = rand() % (N_CITIES - 1);
    int i;
    for( i = 0; i < spot; i++ )
        new_ind[i] = left[i];
    for( ; i < N_CITIES; i++)
        new_ind[i] = right[i];
}
