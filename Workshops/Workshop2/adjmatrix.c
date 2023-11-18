#include "stdio.h"
#include <stdlib.h>

// Forward declaration of functions
void degree_calc(int N, int* graph_array);
void two_hop_paths(int N, int* graph_array);


int main() {

    FILE * fp; // initialize file pointer
    fp = fopen("testgraph.txt", "r"); // open file for reading

    int N; // number of vertices
    fscanf(fp, "%d", &N); // read the first line of the file and assign to N
    
    //printf("Number of vertices: %d\n", N);

    int * graph_array = malloc(sizeof(int)*N*N); // initialize array of size NxN 

    // Read in the rest of the file and store in graph_array
    for (int i=0; i < N*N; i++) {
        fscanf(fp, "%d", &graph_array[i]);
        //printf("%d ", graph_array[i]);
    }

    // Close the file
    fclose(fp);

    // Calculate in and out degrees of each edge
    degree_calc(N, graph_array);
    // Find all two_hop_paths
    two_hop_paths(N, graph_array);

    // free the memory allocated to graph_array
    free(graph_array); 

    return 0;
}



void degree_calc(int N, int* graph_array){
    // Calculate in and out degrees
    // In degree of vertex i is the sum of the ith column
    // Out degree of vertex i is the sum of the ith row
    int in_degree;
    int out_degree;
    for (int i=0; i<N; i++){
        // Calculate the in degree
        in_degree = 0;
        for (int k=i; k < N*N; k +=N){
            in_degree += graph_array[k];
        }
        // Calculate the out degree
        out_degree = 0;
        for (int k= i *N; k < (i+1)*N; k++){
            out_degree += graph_array[k];
        }
        printf("%d: %d, %d\n", i, in_degree, out_degree);
    }
}


void two_hop_paths(int N,int* graph_array){
    // printf("Now we find all 2 hop paths\n");
    // Find all 2 hop paths with distinct vertices

    // For every vertex
    for (int i=0; i<N; i ++){
        // For every connected vertex
        for (int k = i * N; k < (i+1)*N; k++)
        {
            if (graph_array[k] == 1) // K is a potential middle node
            { 
                int v_2 = k - i * N; // v_2 is the vertex number of k
                // Now we check k's outbound vertices to find all j that we can connect from K
                for (int j = v_2 * N; j < (v_2 + 1) * N; j++) 
                {
                    // Check if we found a path
                    if (graph_array[j] == 1)
                    { 
                        int v_3 = j - v_2 * N; // v_3 is the vertex number of j
                        if (v_3 != i) // Check if v_3 is the same as i
                        {
                            printf("%d %d %d \n", i , v_2 ,v_3);
                        }
                    }
                }
            }
        }
    }

}