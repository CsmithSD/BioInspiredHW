#include "../include/genetic_programming.h"

int main()
{
    genetic_programming();
    return 0;
}

void genetic_programming()
{
    srand(time(NULL));
    struct bin_tree *trees = (struct bin_tree*) malloc( sizeof(struct bin_tree) * POP ); 
    bool correct[POP][21];
    double fit_vals[POP];
    int i, j, left, right;
    
    initpop(trees);
    fitness(trees, correct, fit_vals);
    sort_trees( trees, fit_vals );
    for( i = 0; i < GEN; i++ )
    {
       for( j = POP/2; j < POP; j++)
       {
            left  = rand() % ( POP / 2 );
            right = rand() % ( POP / 2);
            recomb( &trees[left], &trees[right],&trees[j]);
            recursive_mutate( ( rand() % 255 ), &trees[j]);
       }
       fitness(trees, correct, fit_vals);
       sort_trees(trees, fit_vals);
    }
    printf("Individual: ");
    print_tree(&trees[0]);
    printf( "Percent Correct: %f\n", fit_vals[0]);
}
void print_pop( struct bin_tree *trees, double fit_vals[] )
{
    for( int i = 0; i < POP; i++ )
    {
        printf("Individual: ");
        print_tree( &trees[i] );
        printf(")");
        printf( "Percent Correct: %f\n", fit_vals[i]);
    }
}

void print_tree( struct bin_tree *tree)
{
    if( tree -> left_child != 0 )
    {
        printf( "( ");
        print_tree( tree -> left_child);
    }
    
    printf(" %c ", tree->value);

    if( tree -> right_child != 0 )
    {
        print_tree( tree -> right_child);
        printf(" )");
    }
}

void initpop( bin_tree *trees )
{
    for( int i = 0; i < POP; i++)
            rec_init( &trees[i], 0, rand() % 15  );
}

void rec_init( struct bin_tree *parent, short int depth, short int num_children)
{
    int num_left = num_children % (15/(depth+2));
    int num_right = num_children - num_left;

    parent -> left_child  = 0;
    parent -> right_child = 0;
    parent -> depth = depth;
    if(num_children > 0 && depth != 4)
    {
        parent -> left_child  = ( struct bin_tree*) malloc( sizeof( struct bin_tree) );
        rec_init( parent -> left_child, depth+1, num_left );

        if( num_right >= 0 )
        {
            parent -> right_child = ( struct bin_tree*) malloc( sizeof( struct bin_tree) );
            rec_init( parent -> right_child, depth + 1, num_right );
        }
    }

    if( parent->left_child == 0 && parent -> right_child == 0 )
        parent->value = generate_terminal();
    else
    {
        parent -> value = generate_operator();
        if( parent -> left_child == 0)
        {
            parent->left_child = ( struct bin_tree*) malloc( sizeof( struct bin_tree ) );
            parent -> left_child -> value = ( parent -> value == '*' ) ? '1' : '0';
        }
        if(parent -> right_child == 0 )
        {
            parent -> right_child = ( struct bin_tree*) malloc( sizeof( struct bin_tree ) );
            parent -> right_child -> value  = ( parent->value == '*' ) ? '1' : '0';
        }
    }
}

char generate_terminal()
{
    switch (rand() % 7)
    {
        case 0:  return '0';
        case 1:  return '1';
        case 2:  return '2';
        case 3:  return '3';
        case 4:  return '4';
        case 5:  return '5';
        default: return 'x';
    }
}

char generate_operator()
{
    switch( rand() % 4 )
    {
        case 0:
        case 1:  return '+';
        default: return '*';
    }
}

void recomb( struct bin_tree *tree_1, struct bin_tree *tree_2, struct bin_tree *new_tree )
{
    char spot1 = rand()%256;
    char spot2 = rand()%256;

    if( (spot1 & 3) == 0 || (spot1 & 3) == 3 )
        spot1 ^= 1;
    if( (spot2 & 3) == 0 || (spot2 & 3) == 3 )
        spot2 ^= 2;
    //initialise root node of tree
    clear_tree( new_tree );
    new_tree -> value = generate_operator();
    new_tree -> depth = 0;
    
    //creates left side of tree
    recursive_recomb( spot1, tree_1, new_tree);
    //creates right side of tree
    recursive_recomb( spot2, tree_2, new_tree);
}

void recursive_recomb(char spot, struct bin_tree* tree, struct bin_tree* new_tree)
{
    int i;
    char find_spot = 3;
    char path;
    for( i = 0; i < tree -> depth; i++)
        find_spot <<= 2;
    
    path = spot & find_spot;

    for( i = 0; i < tree -> depth; i++)
        path >>= 2;
    
    if( path == 1  && tree -> left_child != 0)
        recursive_recomb( spot, tree -> left_child, new_tree);
    
    else if( path == 2 && tree -> right_child != 0)
        recursive_recomb( spot, tree -> right_child, new_tree );
    //if random stoping point is found current subtree is copied into new tree
    else
    {
        if( new_tree -> left_child == 0 )
        {
            new_tree->left_child = (struct bin_tree*) malloc( sizeof(struct bin_tree));
            recomb_copy( tree, new_tree -> left_child, 1 );
        }
        else
        {
            new_tree -> right_child = ( struct bin_tree* ) malloc( sizeof( struct bin_tree ));
            recomb_copy( tree, new_tree -> right_child, 1 );    
        }
    }   
}
void recomb_copy( struct bin_tree *tree, struct bin_tree *new_tree, int depth )
{
    if(tree-> right_child != 0)
    {
        new_tree -> right_child = ( struct bin_tree* ) malloc( sizeof( struct bin_tree ));
        recomb_copy( tree -> right_child, new_tree -> right_child, depth + 1 );
    }
    else
        new_tree -> right_child = 0;
    
    if( tree-> left_child != 0 )
    {
        new_tree -> left_child = ( struct bin_tree* ) malloc( sizeof( struct bin_tree ));
        recomb_copy( tree -> left_child, new_tree -> left_child, depth + 1 );
    }
    else
        new_tree -> left_child = 0;

    new_tree -> value = tree -> value;
    new_tree -> depth = depth;
}


void recursive_mutate(char spot, struct bin_tree* tree)
{
    int i;
    char find_spot = 3;
    char path;
    for( i = 0; i < tree -> depth; i++)
        find_spot <<= 2;
    
    path = spot & find_spot;

    for( i = 0; i < tree -> depth; i++)
        path >>= 2;
    
    if( path == 1  && tree -> left_child != 0)
        recursive_mutate( spot, tree -> left_child );
    
    else if( path == 2 && tree -> right_child != 0)
        recursive_mutate( spot, tree -> right_child );
    else
        mutate_node( tree );
}

void mutate_node( struct bin_tree *tree )
{
    char old_value = tree->value;
    switch( tree->value)
    {
        case '*':
            tree->value = '+';
            break;
        case '+':
            tree->value = '*';
            break;
        default:
            while( old_value == tree->value )
                tree->value = generate_terminal();
    }
}

int evaluate_tree( struct bin_tree* tree, int x_val)
{
    //if value is a terminal
    if( tree -> value != '+' && tree -> value != '*' )
        return terminal_to_int( tree -> value, x_val); //returns the int value of a terminal x_val if terminal is x
    //if value is * add the two subtrees
    if(tree -> value == '*' )
        return evaluate_tree( tree -> left_child, x_val) * evaluate_tree( tree -> right_child, x_val);
    //if value is + add the two subtrees
    return evaluate_tree( tree -> left_child, x_val) + evaluate_tree( tree -> right_child, x_val);
}

int terminal_to_int( char term, int x_val )
{
    switch( term )
    {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        default:  return x_val;
    }
}

void fitness( struct bin_tree *trees, bool correct[][21], double fit[] )
{
    int x, i;
    for( i = 0; i < POP; i++)
    {
        for( x = -10; x < 10; x++ )
            correct[i][x] = check_answer( x, evaluate_tree( &trees[i], x) );
        fit[i] = calc_fit( correct[i] );
    }
}

bool check_answer( int x_val, int answer)
{
    const int correct_answers[21] = { 153, 120, 91, 66, 45, 28, 15, 6, 1, 0, 3, 10, 
        21, 36, 55, 78, 105, 136, 171, 210, 253 };
    if( correct_answers[x_val + 10] == answer )
        return true;
    return false;
}
double calc_fit( bool correct[] )
{
    int num_right = 0;
    int i;
    for( i = 0; i < 21; i++ )
        if( correct[i] )
            num_right++;
    return num_right/21.0;
}

void clear_tree( struct bin_tree *tree)
{
    //removes left side of tree freeing up memory
    if( tree -> left_child != 0 )
    {
        clear_tree( tree-> left_child );
        free( tree -> left_child );
        tree -> left_child = 0;
    }
    //removes right side of tree freeing up memory
    if( tree -> right_child != 0 )
    {
        clear_tree( tree -> right_child );
        free( tree -> right_child );
        tree -> right_child = 0;
    }
}

void sort_trees( struct bin_tree *trees, double fit_vals[] )
{
    bool swapped = true;
    double tmp;
    int j = 0;
    while(swapped)
    {
        swapped = false;
        j++;
        for( int i = POP-1; i > 0; i--)
        {
            if(fit_vals[i] > fit_vals[i-1] )
            {
                tmp = fit_vals[i];
                fit_vals[i] = fit_vals[i-1];
                fit_vals[i-1] = tmp;

                swapped = true;
                
                char tmp_val;
                
                tmp_val = trees[i].value;
                trees[i].value = trees[i-1].value;
                trees[i-1].value = tmp_val;
                swap_subtrees( &trees[i], &trees[i-1]);

             }
        }
    }
}

void swap_subtrees( struct bin_tree *tree1, struct bin_tree *tree2)
{
    struct bin_tree *tmp;

    tmp = tree1 -> left_child;
    tree1 -> left_child = tree2 -> left_child;
    tree2 -> left_child = tmp;
    
    tmp = tree1 -> right_child;
    tree1 -> right_child = tree2 -> right_child;
    tree2 -> right_child = tmp;
    tmp = 0;
}

