#include <stdio.h>
#include <stdlib.h>

// Struct of pointer to next node
typedef struct node {
    int vertex;
    struct node* next; // pointer to next vertex
} node;

// Struct for graph
typedef struct Graph {
    int n_vertices;
    node** adj_lists; // array of pointers
} Graph;

// Function Prototypes
void addEdge(Graph* graph, int from, int to);
void DFS(Graph* graph, int startVertex, int* visited);

void printGraph(Graph* graph); // for debugging

int main(int argc, char *argv[]) {
    char *file_name = argv[1]; // first argument is filename
    int mode = atoi(argv[2]); // second argument is mode: 1 or 2 - convert to int

    int n_vertices; // number of vertices
    int count_cc = 0; // count of connected components

    // ---------- Read file and build the graph ---------
    FILE *fp = fopen(file_name, "r"); // open file in read mode
    fscanf(fp, "%d", &n_vertices); // read first line get number of vertices

    // Allocate memory for graph
    Graph* graph = malloc(sizeof(Graph));
    graph->n_vertices = n_vertices;
    graph->adj_lists = malloc(sizeof(node*) * n_vertices);

    // Initialize each adjacency list as empty
    for (int i = 0; i < n_vertices; i++) {
        graph->adj_lists[i] = NULL; // Initialize each individual value to null
    }

    // Read Edges from file and build graph
    int from_vertex, to_vertex, connection;
    while (fscanf(fp, "%d %d %d", &from_vertex, &to_vertex, &connection) != EOF) {
        if (connection <= mode) {
            addEdge(graph, from_vertex, to_vertex);
        }
    }
    fclose(fp); // close file

    // Initialize visited array as all zeros
    int* visited = malloc(sizeof(int) * n_vertices);
    for (int i = 0; i < n_vertices; i++) {
        visited[i] = 0;
    }

    // Run DFS on the graph
    for (int i = 0; i < n_vertices; i++) {
        if (visited[i] == 0) {
            DFS(graph, i, visited);
            count_cc++; // increment our counter
        }
    }

    // Handle Edge Cases manually just in case
    if (n_vertices == 1) {
        count_cc = 1;
    } else if (n_vertices == 0) {
        count_cc = 0;
    }


    // Print graph - debugging
    //printGraph(graph);

    // Print output
    printf("%d\n", count_cc);

    // Free memory
    for (int i = 0; i < n_vertices; i++) {
        node* temp = graph->adj_lists[i];
        while (temp) {
            node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adj_lists);
    free(graph);
    free(visited);

    return 0;
}


// Run dfs on the graph
void DFS(Graph* graph, int startVertex, int* visited) {
    visited[startVertex] = 1; // set visited to true

    node* temp = graph->adj_lists[startVertex]; // get first element of adj list of startVertex

    while (temp) { // while this isnt null
        int connectedVertex = temp->vertex; // we get the vertex that this node is pointing to
        if (visited[connectedVertex] == 0) { // if this isn't visited , run dfs on it
            DFS(graph, connectedVertex, visited);
        }
        temp = temp->next; // move to the next element in the adj list of start vertex
    }
}


// Function to add an edge
void addEdge(Graph* graph, int from, int to) {
    node* newNode = malloc(sizeof(node)); // allocate memory for a new node

    newNode->vertex = to; // the value of the node is the "to" vertex, so this indicates an edge to the "to" vertex
    
    newNode->next = graph->adj_lists[from]; // this node in turn will point to the first element of the adj list of the from vertex
    // so we are prepending it to the adj list
    
    graph->adj_lists[from] = newNode;
}


// Function to print the graph for debugging purposes
void printGraph(Graph* graph) {

    for (int i = 0; i < graph->n_vertices; i++)  // loop through all vertices
    {
        node* temp = graph->adj_lists[i]; // get first element of adj list of node i
        printf("Vertex %d: ", i); // print vertex
        while (temp) { // Print the elements of the adj list while temp is not null
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n"); // Null at the end
    }
}