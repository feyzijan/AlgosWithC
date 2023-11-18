// Find diameter using All-pairs shortest paths
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "graph.h"

// #define DEBUG

//===================== Function Prototypes ===========================
void PrepareGraph(int* mygraph);
int calcIterations();
void CalcShortestPaths(int* mygraph);
int CalcDiameter(int* mygraph);
void PrintGraph(int* mygraph);

//========================= Main Function ===========================
int main() {
// initialize the graph here; note it is a 1-dimensional array	
	int* mygraph = (int *) malloc(sizeof(int) * NVERT * NVERT);
	getGraph(mygraph);

	int i, j, k;

#ifdef DEBUG
	printf("\nThe adjacency matrix is\n");
	PrintGraph(mygraph);
#endif

// prepare the graph/array for the all-pairs algorithm
	PrepareGraph(mygraph);

#ifdef DEBUG
	printf("\nThe matrix for calculating all-pairs shortest paths is\n");
	PrintGraph(mygraph);
#endif
	
// set up outer iteration
	int niterations = calcIterations();
#ifdef DEBUG
	printf("number of iterations = %d\n",niterations);
#endif

// calculate shortest paths	
	for(int iiteration = 0; iiteration < niterations; iiteration++) {
#ifdef DEBUG
		printf("\nouter iteration %d:\n",iiteration);
#endif
		CalcShortestPaths(mygraph);
	} 
	
#ifdef DEBUG
	printf("\nThe graph diameter is ");
#endif
	printf("%d\n",CalcDiameter(mygraph));

	free(mygraph);
	return 0;
}

//===================== Function Definitions ===========================

// store "Infinity" values (INT_MAX) where there are no edges, other than from each edge to itself
void PrepareGraph(int* mygraph) {
	// loop through 1d array
	for(int i = 0; i < NVERT; ++i) {
        for(int j = 0; j < NVERT; ++j) {

			if(i != j) { // skip diagonal entries
                if(mygraph[i * NVERT + j] == 0) { // If there's no edge  set value to INT_MAX
                    mygraph[i * NVERT + j] = INT_MAX;
                }
			}
        }
    }
}

int calcIterations() {

	return (int)ceil(log(NVERT - 1) / log(2));
}

// calculate the lengths of all shortest paths using the "matrix multiplication" method
// we need to compute shortest paths using at most n-1 edges
// we start by calculatting A^2, then A^4, A^8, etc until we get to A^(n-1)
void CalcShortestPaths(int* mygraph) {
    int* temp = (int *) malloc(sizeof(int) * NVERT * NVERT);
    int* result = (int *) malloc(sizeof(int) * NVERT * NVERT);

    // Copy initial graph to result
    for (int i = 0; i < NVERT * NVERT; ++i) {
        result[i] = mygraph[i];
    }

    int iterations = calcIterations();
    for(int i = 0; i < iterations; ++i) {
        // Multiply result by itself and store it in temp
        matrixMultiply(result, result, temp, NVERT);
        
        // Copy temp back to result for the next iteration
        for (int i = 0; i < NVERT * NVERT; ++i) {
            result[i] = temp[i];
        }
    }

    // Copy final result back to mygraph
    for (int i = 0; i < NVERT * NVERT; ++i) {
        mygraph[i] = result[i];
    }

    free(temp);
    free(result);
}


// calculate the diameter of the graph as the maximum of the minimum distances
int CalcDiameter(int* mygraph) {
	 // Initialize diameter to an invalid value
    int diameter = -1;

    // Loop through all pairs of vertices
    for(int i = 0; i < NVERT; ++i) {
        for(int j = 0; j < NVERT; ++j) {
            // Skip same vertex and non-connected vertices
            if(i != j && mygraph[i * NVERT + j] != INT_MAX) {
                // Update diameter with the max value
				if (mygraph[i * NVERT + j] > diameter) {
					diameter = mygraph[i * NVERT + j] ;
				} 
			}
        }
    }
    return diameter;
}

// print all array entries as an adjacency matrix
void PrintGraph(int* mygraph) {
	for (int i=0; i<NVERT; i++) {
		for (int j=0; j<NVERT; j++) {
			printf("%d ", mygraph[i*NVERT+j]);
		}
		printf("\n");
	}
}