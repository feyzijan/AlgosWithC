# CSE 6010 - Assignment 3: Connected Components

## Overview

This program, developed for the CSE 6010 assignment, is designed to analyze a network of social contacts exposed to a transmissible disease, represented by an undirected graph. The vertices signify individuals, and the edges, labeled either 1 or 2, indicate the frequency of contact. The program computes the number of connected components in the graph, which helps quantify aspects of disease transmissibility.

## Program Structure

The program, written in C, reads a graph from a file and represents it using an adjacency list with dynamically allocated memory. It utilizes a variant of Depth-First Search (DFS) to identify connected components, considering edges based on their label as specified by command-line arguments.

## Key Features

- **Dynamic Memory Usage:** Utilizes `malloc` for creating nodes, graphs, and adjacency lists.
- **Structures:** Employs a `Node` struct for adjacency list elements and a `Graph` struct for maintaining the graph.
- **Control Flow:** Incorporates while and for loops for reading edges and initializing lists; if statements handle edge weights and check for unvisited nodes during DFS.

## Validity

The program's effectiveness is ensured by:
- **Memory Management:** No memory leaks as verified by Valgrind.
- **Edge Cases Handling:** Appropriately addresses graphs with zero or one vertex.
- **Graph Integrity:** Includes a `print_graph` function (commented out for submission) to ensure the graph is read and created correctly.
- **Connected Components Count:** Standard recursive DFS implementation to count connected components accurately, including isolated vertices.

For a detailed explanation of program development and structure, and an account of why the program functions correctly, please refer to the explanatory slides provided alongside this documentation.

Compile via the makefule by running "make" and then "./connected" in the terminal
Compiler: GCC
OS: Apple M1 MAC OS 13.5.2 
