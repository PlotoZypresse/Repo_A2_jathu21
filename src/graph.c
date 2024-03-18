#include "Graph.h"
#include "LinkedList.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>

// Allocates and constructs a new graph with n vertices.
// Returns a pointer to the new graph, or NULL on error.
// Post: the caller owns the graph.
Graph *Graph_new(int n){
    //check if graph has 0 or less vertticies
    if(n <= 0){
        fprintf(stderr, "0 or less verticies\n");
        return NULL;
    }

    // Allocate a new graph
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    // for allocation failure
    if(newGraph == NULL){
        fprintf(stderr, "Graph allocation failed\n");
        return NULL;
    }

    // set number of verticies and edges
    newGraph->numVertices = n;
    newGraph->numEdges = 0;

    // allocate verticies
    newGraph->vertices = (Vertex*)malloc(n * sizeof(Vertex));
    // allocation failure
    if (newGraph->vertices == NULL) {
        fprintf(stderr, "Memory allocation for vertices failed\n");
        free(newGraph);  // Free the previously allocated memory
        return NULL;
    }

    // initialize each vertex
    for (int i = 0; i < n; ++i) {
        newGraph->vertices[i].id = i;
        newGraph->vertices[i].outNeighbours = LinkedList_new();
        newGraph->vertices[i].inNeighbours = LinkedList_new();
    }
    return newGraph;
}

// Adds an edge from the i'th to the j'th vertex (0-indexed).
void Graph_addEdge(Graph *g, int i, int j){
    
    // check if i and j are in a valid range for verticies
    if(i < 0 || i >= g->numVertices || j < 0 || j >= g->numVertices){
        fprintf(stderr, "Invalid vertices: %d, %d\n", i, j);
    }

    //check if the edge already exists
    LinkedListNode *exEdge = LinkedList_find(g->vertices[i].outNeighbours,&g->vertices[j]);
    if(exEdge != NULL){
        fprintf(stderr, "Edge already exists between %d and %d\n", i, j);
    }

    //add the edge from i to j to the linked list. Including in and out ll
    LinkedList_append(g->vertices[i].outNeighbours, &g->vertices[j]);
    LinkedList_append(g->vertices[j].inNeighbours, &g->vertices[i]);

    //increment the number of edges
    g->numEdges++;
}

// Reads a graph from the given file and returns a newly
// constructed Graph representing it.
// Returns a pointer to the read graph, or NULL on error.
// Post: the caller owns the graph.
Graph *Graph_read(const char *filename){

    // open file in read mode
    // open fail
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        fprintf(stderr, "can not open file");
    }

    //getting the int from line 0 to get the number of edges
    int numberOfVerticies;
    if(fscanf(file, "%d", &numberOfVerticies)==1){
        //printf("number of verticies: %d\n", numberOfVerticies);
    }
    else{
        fprintf(stderr, "couldnt read number of verticies from file");
    }
    
    //allocates the graph with the number of verticies
    Graph *graph = Graph_new(numberOfVerticies);
    if (graph == NULL) {
        fclose(file);
        return NULL;
    }
    
    // Declare a buffer to store each line read from the file
    char *buffer = NULL;
    // Initialize the size of the buffer to 0
    size_t buffer_size = 0;
    // Variable to store the number of characters read by getline
    ssize_t read;

    // Variable to keep track of the source vertex in the graph
    int sourceVertex = -1;

    //read lines from the file until the end of the file
    while ((read = getline(&buffer, &buffer_size, file)) != -1) {
        // iterate throug the line except \n
        for(int j = 0; j<read-1; j++){
            int value;
            // Use sscanf to parse a single digit from the current position in the buffer
            if (sscanf(&buffer[j], "%1d", &value) == 1) {
                // Check if the digit is 1
                if (value==1){
                    // add an edge from sourceVertex to j
                    Graph_addEdge(graph, sourceVertex, j);
                }  
            }
        }
        // go to the next vertex for the next line
        sourceVertex++;
    }

    // free buffer and close file
    free(buffer);
    fclose(file);

    return graph;
}

// Deallocates the given graph and all its associated memory.
void Graph_delete(Graph *g){
    // delete the linked lists in and out Neighbours
    for(int i = 0; i < g->numVertices; i++){
        LinkedList_delete(g->vertices[i].inNeighbours);
        LinkedList_delete(g->vertices[i].outNeighbours);
    }
    // free the graphs verticies and the graph
    free(g->vertices);
    free(g);
}

// Prints some useful information about the given graph.
// can be used to print the number of verticies, the vertex id, out and in neighbours
void Graph_print(Graph *g){
    printf("number of vertices %d\n", g->numVertices);

    for(int i = 0; i < g->numVertices; i++){
        printf("Vertex ID: %d\n", g->vertices[i].id);
        
        printf("Out Neighbours: ");  
        LinkedListNode *outNeighbours = g->vertices[i].outNeighbours->head;
        while (outNeighbours != NULL){
            Vertex *neighbour = (Vertex*)outNeighbours->data;
            printf("%d ", neighbour->id);
            outNeighbours = outNeighbours->next;
        }
        printf("\n");

        printf("In Neighbours: ");  
        LinkedListNode *inNeighbours = g->vertices[i].inNeighbours->head;
        while (inNeighbours != NULL){
            Vertex *neighbour = (Vertex*)inNeighbours->data;
            printf("%d ", neighbour->id);
            inNeighbours = inNeighbours->next;
        }
        printf("\n\n");
    }
 
}

