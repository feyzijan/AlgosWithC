#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

typedef struct {
    int u;
    int v;
    double w;
}Edge;



int main (int argc, char* argv[]) {

    // Read command line arguements
    char * inputFile = argv[1]; // input file name
    int n_threads = atoi(argv[2]); // number of threads

    // Read file and store graph
    int n_vertices;
    int n_edges;

    FILE * fp = fopen(inputFile, "r");
    // get number of vertices and edges
    fscanf(fp, "%d %d", &n_vertices, &n_edges);

    // allocate memory for graph - array of pointers to edges, each having 3 ints
    // first memory for array of pointers to int
    Edge * graph = malloc(sizeof(Edge) * n_edges);

    // Read in Graph
    for (int i=0; i<n_edges; i++) {
        fscanf(fp, "%d %d %lf ", &graph[i].u, &graph[i].v, &graph[i].w);
    }

    fclose(fp);



    // Initialize distance array to infinity and predecessor array to 0
    double * dist = malloc(sizeof(double) * n_vertices);
    int * pred = malloc(sizeof(int) * n_vertices);
    for (int i=0; i<n_vertices; i++) {
        dist[i] = 1E9;
        pred[i] = 0;
    }
    // mark source vertex
    dist[0] = 0;
    
    // Belman Ford
    omp_set_num_threads(n_threads);
    double start_time = omp_get_wtime();
    
    // Loop through each edge n_edges - 1 times
    for (int i=1; i<n_vertices; i ++){
        int flag = 0;
        #pragma omp parallel for reduction(|:flag) // or operation on all the flags of all threads
        for (int i=0; i<n_edges-1; i++) {
            // get edge info for edge from u to v
            int u = graph[i].u;
            int v = graph[i].v;
            double w = graph[i].w;
            // relax edge
            if (dist[u] != 1E9 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; // update distance
                pred[v] = u; // update predecessor
                flag = 1;
            }
        }
        if (!flag) break; // No update, exit loop
    }


    double end_time = omp_get_wtime();



    // No need to check for negative cycles

    // Output Based on Command Line Arguements
    if (argc == 4){
        // output results for a single vertex
        int j = atoi(argv[3]);
        if (dist[j] == 1E9) 
        {
            printf("%d: INFTY; %d\n", j, j);
        } 
        else 
        {
            // first print distance to vertex
            printf("%d: %.5f;", j, dist[j]);
            // Now need to print the reverse path - Reverse the path and store in an array
            int * reverse_path = malloc(sizeof(int) * n_vertices);             // allocate memoery - can have at most n_vertices
            int last_index = 0; // will tell us when to start printing

            reverse_path[0] = j; // this node itself first

            int prev = j; // the 

            while (prev != 0) {
                last_index ++;
                reverse_path[last_index] = pred[prev];
                prev = pred[prev];
            }
            // Now print the reverse path
            for (int i=last_index; i>=0; i--) {
                printf(" %d", reverse_path[i]);
            }
            printf("\n");
            free(reverse_path);
        }
   
    } else{
        // output results for all vertices
        for (int j=0; j<n_vertices; j++) 
        {
            if (dist[j] == 1E9)
            {
                printf("%d: INFTY; %d\n", j, j);
            } 
            else 
            {
                // first print distance to vertex
            printf("%d: %.5f;", j, dist[j]);
            // Now need to print the reverse path - Reverse the path and store in an array
            int * reverse_path = malloc(sizeof(int) * n_vertices);             // allocate memoery - can have at most n_vertices
            int last_index = 0; // will tell us when to start printing

            reverse_path[0] = j; // this node itself first

            int prev = j; // the 

            while (prev != 0) {
                last_index ++;
                reverse_path[last_index] = pred[prev];
                prev = pred[prev];
            }
            // Now print the reverse path
            for (int i=last_index; i>=0; i--) {
                printf(" %d", reverse_path[i]);
            }
            printf("\n");
            free(reverse_path);
            }
        }
    }



    // Free memorys
    free(graph);
    free(dist);
    free(pred);
    


    // Print out time for debugging
    printf("%.5f", end_time - start_time);

    return 0;
}