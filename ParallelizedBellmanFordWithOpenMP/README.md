
# Parallel Bellman-Ford Algorithm in C

## Overview
This program implements the Bellman-Ford algorithm in parallel using OpenMP in C. The Bellman-Ford algorithm is used for finding the shortest paths from a single source vertex to all other vertices in a weighted graph. This implementation is particularly useful for large graphs, where parallel processing can significantly reduce computation time.

## Features
- **Parallel Processing**: Utilizes OpenMP for parallelizing the core loop of the Bellman-Ford algorithm.
- **Flexible Input**: Reads graph data from a file.
- **Customizable Output**: Can output shortest paths for either all vertices or a specified vertex.
- **Precision Output**: Prints path costs with a precision of five decimal places.

## Requirements
- GCC Compiler with OpenMP support.
- An input file containing graph data in the specified format.

## Input File Format
The input file should have the following format:
- The first line contains two integers: the number of vertices and the number of edges.
- Each subsequent line represents an edge and should contain two integers (the source and destination vertices) and a double (the edge weight).

Example:
```
4 5
0 1 5.0
0 2 10.0
1 3 4.0
2 1 3.0
3 2 1.0
```

## Compilation
Compile the program using the following command:
```
gcc -fopenmp -o bellman_ford bellman_ford.c
```

## Usage
Run the program with the following command:
```
./bellman_ford <input_file> <number_of_threads> [specific_vertex]
```
- `<input_file>`: Name of the file containing graph data.
- `<number_of_threads>`: Number of threads to use for parallel processing.
- `[specific_vertex]`: (Optional) Specify a vertex to get its shortest path only.

## Example
```
./bellman_ford graph.txt 4 2
```
This will run the program on `graph.txt` using 4 threads and output the shortest path to vertex 2.

## Note
- The program assumes that the graph does not contain negative weight cycles.
- Paths are calculated and stored in reverse order for efficiency.