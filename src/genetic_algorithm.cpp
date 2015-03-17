#include "../include/genetic_algorithm.h"
int main()
{
    genetic_algorithm();
    return 0;
}

void genetic_algorithm( )
{
    char population[POP][SIZE];
    double ans, fitness[POP];
    int i, j, mom, dad;
    srand( time(NULL) );
    initpop(population);
    fitpop(population, fitness);
    sort( population, fitness );
    printf("First population:\n");
    printpop( population, fitness );
    for( i = 0; i < GEN; i++ );
    {
        for( j = POP/2; j < POP; j++)
        {
            mom = rand() % (POP/2);
            dad = rand() % (POP/2);
            recomb( population[mom], population[dad], population[j] );
            mutate( population[j] );
            fitness[j] = fit( encode( population[j] ) );
        }
        sort( population, fitness);
    }
    printf("\nLast population:\n");
    printpop(population, fitness);
    ans = encode( population[0] );
    printf( "Approximate answer is %f\n", ans );
}


void initpop( char population[][SIZE] )
{
    int max = pow(2,BITS);
    for( int i = 0; i < POP; i++ ) 
        dec2bin( rand() % max, population[i]);
}

void printpop(char population[][SIZE], double fitness[])
{
    for( int i = 0; i < POP; i++ )
        printf("Individual = %s, Decimal = %f, Fitness = %f\n", 
                population[i], encode( population[i] ) , fitness[i]);
}
//Maps the value between [-2,2]
double encode(char *string)
{
    int val = bin2dec(string);
    double max = pow(2.0, BITS);
    return val/max;
}
//Maps the value into a binary int value and stores in char array with dec2bin
void decode( double value, char *string )
{ 
    int temp = ( pow(2,BITS) ) * ( value+2.0 ) / 4.0;
    dec2bin(temp, string);
}

void mutate( char *string )
{
    int location = rand()%BITS;
    string[location] = (string[location] == '1') ? '0' : '1';
}

void recomb( char *string1, char *string2, char *string3 )
{
    int i, location = rand() % BITS;
    for( i = 0; i < location; i++ ) string3[i] = string1[i];
    for( ; i < BITS; i++) string3[i] = string2[i];
}

int bin2dec( char* string )
{
    int i, value = 0, pow = 1;
    for( i = BITS-1; i >= 0; pow <<= 1)
        if(string[i--] == '1') value += pow;
    return value;
}

void dec2bin(int val, char *string)
{
    int i;
    string[BITS] = '\0';
    for( i = BITS-1; i >= 0; val>>=1)
        string[i--] = (val%2) ? '1' : '0';
}

void fitpop( char population[][SIZE], double fitness[] )
{
    for( int i = 0; i< POP; i ++ )
        fitness[i] = fit( encode(population[i] ) );
}

void sort( char population[][SIZE], double fitness[])
{
    bool swapped = true;
    double tmp;
    int j = 0;
    char pop_tmp[POP];
    while(swapped)
    {
        swapped = false;
        j++;
        for( int i = POP-1; i > 0; i--)
        {
            if( fitness[i] > fitness[i-1])
            {
                tmp = fitness[i];
                fitness[i] = fitness[i-1];
                fitness[i-1] = tmp;
                
                swapped = true;

                strcpy( pop_tmp, population[i]);
                strcpy( population[i], population[i-1] );
                strcpy( population[i-1], pop_tmp);
            }
        }
    }
}










































