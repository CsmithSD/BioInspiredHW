#include "../include/multilayer_perceptron.h"
#include "../include/simulated_annealing.h"

#define MAX_IT 10
#define LAYERS 2

/*****************************************************************************
 * This function expects a file with the following format:
 * The first line gives the number of patterns to be read in
 * patterns: nPatterns
 * The next pattern is seperated by '-' followd by a 12x10 grid of binary 
 * pixels.
 *
*****************************************************************************/
int multilayer_perceptron(const char* inputFile)
{
    int inputPattern[8][120];
    int desiredOut[3*8] = {0,0,0, 0,0,1, 0,1,0, 0,1,1, 
                            1,0,0, 1,0,1, 1,1,0, 1,1,1};
    vector<vector<double> > neurons;    //the output value of a specific neuron
    vector<vector<vector<double> > > weights;
    vector<vector<double> > deltas;
    vector<vector<double> > desired;
    double MSE = 5.0;
    unsigned int i = 0;
    unsigned int index;
    int NumPatterns;

    //seed random number generator for random() function
    srand(time(NULL));

    //extract the pattern and check
    NumPatterns = extract_pattern(inputFile, inputPattern);
    if( NumPatterns < 0 )
        return -1;

    //initialize 3 neurons in each of the 2 layers and
    //fill neurons[0] with input pattern
    init_neurons(neurons, LAYERS);
    
    //initialize the network weights (2 layers)
    init_weights(weights, LAYERS);

    //Initialize the desired output
    init_desired(desired, desiredOut);

    //initialize deltas
    init_deltas(deltas, LAYERS);

//    check_weights(weights);
//    check_deltas(deltas);
//    check_neurons(neurons);
    printf("*********************\n");

    //Train the ANN
    while( fabs(MSE) > .01 && i < MAX_IT )
    {
        //keeps index within range
        index = i % NumPatterns;

        //stores the index of the pattern into the input layer of the neurons:
        //neuron[0] = patterns[index]
        load_pattern(neurons[0], inputPattern[index]);

        //feed input pattern though the network, updating neurons
        feed_forward(neurons, weights);

        //back propagate the errors and store them as deltas
        MSE = find_deltas(deltas, neurons, weights, desired[index]);

        printf("%dError = %f\n", i, MSE);
        
        //adjust weights
        adjust_weights(weights, neurons, deltas, 1);


        //update iteration count
        i++;
    }
    //End Trainning the ANN

    printf("*********************\n");
//    check_weights(weights);
//    check_deltas(deltas);
//    check_neurons(neurons);



    return 0;
}

void adjust_weights(vector<vector<vector<double> > > &weights, vector<vector<double> > &neurons, vector<vector<double> > &deltas, double learningRate)
{
    for(unsigned int layer = 0; layer < weights.size(); layer++)
    {
        for(unsigned int neuron = 0; neuron < weights[layer].size(); neuron++)
        {
            //update the bias
            weights[layer][neuron][0] += learningRate*deltas[layer][neuron];

            //update all the weights
            for(unsigned int weight = 1; weight < weights[layer][neuron].size(); weight++)
            {
                weights[layer][neuron][weight] += learningRate*deltas[layer][neuron]*neurons[layer][weight-1];
            }
        }
    }
}

void load_pattern(vector<double> &neurons, int* pattern)
{
    //initialize input neurons with the input pattern given
    for(unsigned int i = 0; i < 120; i++)
        neurons[i] = pattern[i];
}

//feeds the input pattern into the network and 
//saves the outputs of all the neurons
void feed_forward(vector<vector<double> > &neurons, vector<vector<vector<double> > > &weights)
{
    double sum = 0.0;

    //Go though each layer
    for(unsigned int layer = 0; layer < weights.size(); layer++)
    {
//        printf("\nLayer %d\n", layer);
        //Go though each neuron
        for(unsigned int neuron = 0; neuron < weights[layer].size(); neuron++)
        {
//            printf("\nNeuron %d\n", neuron);
            //Go though each input weight to the neuron
            for(unsigned int weight = 1; weight < weights[layer][neuron].size(); weight++)
            {
//                printf("%f,", neurons[layer][weight] * weights[layer][neuron][weight]);
                sum += weights[layer][neuron][weight] * neurons[layer][weight];
            }

            //add in the bias
            sum += weights[layer][neuron][0];
            
            //store the outputs for each of the neurons
            neurons[layer+1][neuron] = activation_function(sum);
            sum = 0.0;
        }
    }
}

//This function sets up the structrue of the neurons:
//number of neurons in each layer, number of layers
void init_neurons( vector<vector<double> > &neurons, int layers)
{
    //number of layers
    neurons.resize(layers+1);

    for(unsigned int i = 0; i < neurons.size(); i++)
    {
        //number of neurons in each layer
        //there are 120 input neurons
        neurons[i].resize(i == 0? 120 : 3);
    }

}

void init_desired(vector<vector<double> > &desired, int* desiredOut)
{
    int k = 0;

    //number of input patterns given in the file
    desired.resize(8);

    for(unsigned int i = 0; i < desired.size(); i++)
    {
        //number of desired outputs for a given input pattern
        desired[i].resize(3);
        for(unsigned int j = 0; j < desired[i].size(); j++)
        {
            desired[i][j] = desiredOut[k];
            k++;
        }
    }
}

void init_deltas( vector<vector<double> > &deltas, int layers)
{
    //number of layers
    deltas.resize(layers);

    for(unsigned int i = 0; i < deltas.size(); i++)
    {
        //number of deltas in each layer
        deltas[i].resize(3);
    }

}

//initializes the number of weights for each neuron, along with the values
void init_weights( vector<vector<vector<double> > > &weights, int layers)
{
    //number of layers
    weights.resize(layers);

    //for each layer, set number of neurons
    for(unsigned int i = 0; i < weights.size(); i++)
    {
        //number of neurons in each layer
        weights[i].resize(3);

        //for each neuron, initialize number of weights and their values
        for(unsigned int j = 0; j < weights[i].size(); j++)
        {
            //number of input weights to each neuron
            //initial input layer is set to 121, the rest are set to 4
            //they include the bias at location 0
            weights[i][j].resize(i == 0? 121 : 4);
            
            for(unsigned int k = 0; k < weights[i][j].size(); k ++)
            {
                weights[i][j][k] = random(0, 0.5);
            }
        }
    }

}

inline double activation_function(double x)
{
    return 1.0/( 1.0 + exp(-x) );
}

double find_deltas(vector<vector<double> > &deltas, vector<vector<double> > &neurons, vector<vector<vector<double> > > & weights, vector<double> &desired)
{
    double MSE = 0.0;
    double out = 0;
    double sum = 0;

    //find output layer deltas: out*(1-out)*(desired-out)
    for(unsigned int neuron = 0; neuron < neurons[LAYERS-1].size(); neuron++)
    {
        out = neurons[LAYERS-1][neuron];
        deltas[LAYERS-1][neuron] = 2*out*(1-out)*(out-desired[neuron]);
        printf("Delta: %f\n", deltas[LAYERS-1][neuron]);
        MSE += pow(out - desired[neuron], 2);
    }

    //find deltas for hidden layers
    for(unsigned int i = weights.size() - 1; i > 0; i--)
    {
        //for each node in each layer...
        for(unsigned int j = 0; j < weights[i].size(); j++)
        {
            //calculate the delta using the weights.
            for(unsigned int k = 0; k < deltas[i].size(); k++)
            {
                sum += weights[i][j][k+1] * deltas[i][k];
            }
            deltas[i-1][j] = 2*neurons[i][j]*(1-neurons[i][j])*sum;
            printf("Delta: %f\n", deltas[i-1][j]);
            sum = 0;
        }
    }
    
    return MSE;
}


//check if weight vector got initialized
void check_neurons(vector<vector<double> > &neurons)
{
    printf("//----------neurons----------\n");
    for(unsigned int i = 0; i < neurons.size(); i++)
    {
        printf("Layer %d\n", i);
        for(unsigned int j = 0; j < neurons[i].size(); j++)
        {
            printf("Neuron %d: %f\n", j, neurons[i][j]);
        }
    }
    printf("----------neurons----------//\n");
}

//check if weight vector got initialized
void check_weights(vector<vector<vector<double> > > &weights)
{
    printf("//----------weights----------\n");
    for(unsigned int i = 0; i < weights.size(); i++)
    {
        printf("Layer %d\n", i);
        for(unsigned int j = 0; j < weights[i].size(); j++)
        {
            printf("Neuron %d\n", j);
            for(unsigned int k = 0; k < weights[i][j].size(); k++)
            {
                printf("%f,", weights[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("----------weights----------//\n");
}

void check_deltas(vector<vector<double> > &deltas)
{
    printf("//----------deltas----------\n");
    for(unsigned int i = 0; i < deltas.size(); i++)
    {
        printf("Layer %d\n", i);
        for(unsigned int j = 0; j < deltas[i].size(); j++)
        {
            printf("Neuron delta %d: %f\n", j, deltas[i][j]);
        }
    }
    printf("----------deltas----------//\n");
}

int extract_pattern(const char* inputFile, int patterns[][120])
{
    FILE* fin = fopen(inputFile, "r");
    char buffer[100];
    int numPattern;
    int j = 0; 
    int c = 0;

    if(fin == NULL)
    {
        printf("Could not Open file\n");
        return -1;
    }

    //read in number of patterns
    fgets(buffer, 100, fin);
    numPattern = atoi(strchr(buffer, ' ') );

    //dinamically allocate array with number of patterns


    while( fgets(buffer, 100, fin) != NULL )
    {
        //'-' is to seperate patterns in the file, don't read in
        if(buffer[0] == '-')
        {
            //reset loop variables and continue
            j++;
            c = 0;
            continue;
        }

        //put values in input array
        for(int i = 0; buffer[i] != '\n'; i++)
            patterns[j][i+c] = (buffer[i] == '0')? 0 : 1;


        //update count variable
        c += 10;
        
    }

    //check patterns array
//    for(j = 0; j < 8; j++)
//    {
//        for(int i = 0; i < 120; i++)
//        {
//            if(i % 10 == 0)
//                printf("\n");
//            printf("%d ", patterns[j][i]);
//        }
//        printf("\n");
//    }

    fclose(fin);

    return j;
}
