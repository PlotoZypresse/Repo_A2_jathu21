#include "LinkedList.h"
#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

// Allocate and initialize an empty linked list.
// Returns: a pointer to the new linked list, or NULL on error.
// Post: the caller owns the linked list.
LinkedList *LinkedList_new(){
    
    LinkedList *ll = malloc(sizeof(LinkedList));
	// allocation fail
    if(!ll){
        fprintf(stderr, "memory allocation failed");
        return NULL; 
    } 

	ll->head = NULL;
	ll->tail = NULL;
	ll->size = 0;
	return ll;
}

// Deallocate the given linked list, including all nodes
// (but _not_ the data they point to, the user owns that).
void LinkedList_delete(LinkedList *ll){
    assert(ll);
	// deallocate all nodes
	LinkedListNode *next;

    for(LinkedListNode *node = ll->head; node; node = next){
        //get the next pointer before deleting it
        next = node->next;
        free(node);
    }
    
    // dealocate the ll
    free(ll);
}

// Append a the given element to the list.
// The linked list does _not_ take ownership over the element
// (only the linked list node).
// Returns: a pointer to the node with the new element, or NULL on error.
LinkedListNode *LinkedList_append(LinkedList *ll, void *elem){
    if (ll == NULL) {
        fprintf(stderr, "Invalid linked list\n");
        return NULL;
    }

    // Create a new node
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));

    // allocation fail
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation for node failed\n");
        return NULL;
    }

    // data and next for new node
    newNode->data = elem;
    newNode->next = NULL;

    // if its the first node
    if (ll->tail == NULL) {
        // If the list is empty set both head and tail to the new node
        ll->head = newNode;
        ll->tail = newNode;
    } else {
        // Otherwise add the new node to the end of the list
        ll->tail->next = newNode;
        newNode->prev = ll->tail;
        ll->tail = newNode;
    }

    ll->size++;

    return newNode;
}

// Remove and return the first element from the given list.
// Pre: ll->size != 0
void *LinkedList_popFront(LinkedList *ll){
    //error handling
    if (ll == NULL || ll->size == 0) {
        fprintf(stderr, "Invalid linked list or list is empty\n");
        return NULL;
    }
    // get head, data and next
    LinkedListNode *firstNode = ll->head;
    void *firstElem = firstNode->data;
    ll->head = firstNode->next;
    
    //set new head
    if (ll->head != NULL) {
        ll->head->prev = NULL;
    } else {
        // tail update if list is empty
        ll->tail = NULL;
    }

    // freeing the removed node and size--
    free(firstNode);
    ll->size--;

    return firstElem;
}

// Find the linked list node containing the given element.
// Returns: a pointer to the found node, or NULL if the element was not found.
LinkedListNode *LinkedList_find(LinkedList *ll, void *elem){
    for(LinkedListNode *node = ll->head; node; node = node->next) {
		if(node->data == elem)
			return node;
	}
	return NULL;
}

// Remove the given node from the given linked list (and deallocate it).
// Pre: node must belong to ll
// Returns: node->data
void *LinkedList_remove(LinkedList *ll, LinkedListNode *node){
    if (ll == NULL || node == NULL) {
        fprintf(stderr, "Invalid linked list or node\n");
        return NULL;
    }

    // chedck if node is in linked list
    if (node->prev == NULL && node != ll->head) {
        fprintf(stderr, "Node does not belong to the linked list\n");
        return NULL;
    }

    if (node->prev != NULL) {
        // Update the next pointer of the previous node
        node->prev->next = node->next;
    } else {
        // Update the head if the node is the first in the list
        ll->head = node->next;
    }

    if (node->next != NULL) {
        // Update the prev pointer of the next node
        node->next->prev = node->prev;
    } else {
        // Update the tail if the node is the last in the list
        ll->tail = node->prev;
    }

    void *removedData = node->data;
    free(node);
    ll->size--;

    return removedData;
}