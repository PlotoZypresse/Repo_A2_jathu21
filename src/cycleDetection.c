#include "cycleDetection.h"
#include "Graph.h"
#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Runs Kahn's algorithm on the graph, and outputs 'CYCLE DETECTED!\n'
// if a DAG cannot be created, or the vertices as a list fx. '4, 0, 1, 3, 2\n'
// representing an ordering in the DAG.
// The output is printed to stdout.
// The input may be altered in the process.
void cycleDetection(Graph *g){
    // initialize S and L
    LinkedList *S = LinkedList_new();
    LinkedList *L = LinkedList_new();

    // insert vertecies into S with no inNeighbours
    for(int i = 0; i < g->numVertices; i++){
        if(g->vertices[i].inNeighbours->size == 0){
           LinkedList_append(S, &g->vertices[i]); 
        }
    }

    // Main loop
    while(S->size != 0){
        Vertex *u = LinkedList_popFront(S);
        LinkedList_append(L, u);

        // iterate over out naighbours of u
        LinkedListNode* current = u->outNeighbours->head;
        while(current != NULL){
            Vertex *v = (Vertex*)current->data;
            
            //update incoming count
            v->inNeighbours->size--;
            
            // if v has no more incoming append to S
            if(v->inNeighbours->size == 0){
                LinkedList_append(S, v);
            }

            current = current->next;
        }
    }

    // check for cycles
    for (int i = 0; i < g->numVertices; i++) {
        if(g->vertices[i].inNeighbours->size != 0){
            printf("CYCLE DETECTED!\n");
            LinkedList_delete(S);
            LinkedList_delete(L);
            return;
        }
    }

    // Print the topological order
    LinkedListNode* current = L->head;
    while(current != NULL){
        struct Vertex* vertex = (struct Vertex*)current->data;
        printf("%d", vertex->id);

        // Check if this is the last node before printing a comma
            if (current->next != NULL) {
                printf(", ");
            }
            if (current->next == NULL) {
                printf("\n");
            }
        current = current->next;
        }
        
    // deallocate the created Linked Lists
    LinkedList_delete(S);
    LinkedList_delete(L);
}