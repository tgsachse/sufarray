// Provides an integer queue built using a linked list. Includes
// all typical queue functions and can be any size.
// Written by Tiger Sachse.

#include <stdio.h>
#include <stdlib.h>
#include "suffix_array.h"

// Create a new, empty integer queue.
integer_queue* new_integer_queue(void) {
    return calloc(1, sizeof(integer_queue));
}

// Create a new node with the provided data for an integer queue.
integer_queue_node* new_integer_queue_node(int data) {
    integer_queue_node* new_node;

    if ((new_node = malloc(sizeof(integer_queue_node))) == NULL) {
        return NULL;
    }
    else {
        new_node->data = data;
        new_node->next = NULL;

        return new_node;
    }
}

// Determine if the queue is empty.
int is_empty(integer_queue* queue) {
    return (queue == NULL || queue->head == NULL);
}

// Add a new integer to the queue.
int enqueue(integer_queue* queue, int data) {

    // Can't enqueue into a non-existent queue.
    if (queue == NULL) {
        return OPERATION_FAILURE;
    }

    // If the queue is empty, insert a new node at the head of the queue.
    if (is_empty(queue)) {
        if ((queue->head = new_integer_queue_node(data)) == NULL) {
            return OPERATION_FAILURE;
        }

        queue->tail = queue->head;
    }

    // Otherwise, insert a new node at the back of the queue.
    else {
        if ((queue->tail->next = new_integer_queue_node(data)) == NULL) {
            return OPERATION_FAILURE;
        }

        queue->tail = queue->tail->next;
    }

    return OPERATION_SUCCESS;
}

// Retrieve the data at the front of the queue.
int dequeue(integer_queue* queue) {
    int dequeued_data;
    integer_queue_node* dequeued_node;

    // Can't dequeue from an empty queue! This will also trigger
    // if queue is NULL.
    if (is_empty(queue)) {
        return OPERATION_FAILURE;
    }

    // Save the dequeued node and advance the head pointer.
    // If head becomes NULL then the end of the queue has been reached,
    // so tail must also be set to NULL.
    dequeued_node = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    // Free the dequeued node and return its value.
    dequeued_data = dequeued_node->data;
    free(dequeued_node);

    return dequeued_data;
}

// Print the entire integer queue.
void print_integer_queue(integer_queue* queue) {
    integer_queue_node* current_node;

    if (queue == NULL) {
        printf("Queue is NULL!\n");

        return;
    }

    if (is_empty(queue)) {
        printf("Queue is empty!\n");

        return;
    }

    // Iterate through the queue and print every node's data.
    current_node = queue->head;
    while (current_node != NULL) {
        printf("%d%s", current_node->data, (current_node->next == NULL) ? "\n" : " ");
        current_node = current_node->next;
    }
}

// Destroy an integer queue in memory.
void destroy_integer_queue(integer_queue* queue) {
    integer_queue_node* next_node;

    // Nothing to do!
    if (queue == NULL) {
        return;
    }

    // Destroy all the nodes in the queue's linked list.
    while (queue->head != NULL) {
        next_node = queue->head->next;
        free(queue->head);
        queue->head = next_node;
    }

    // Free the container struct too!
    free(queue);
}

// Destroy an array of integer queues.
void destroy_integer_queues(integer_queue** queues, int size) {
    int index;

    // Nothing to do!
    if (queues == NULL) {
        return;
    }

    // Destroy every queue in the array.
    for (index = 0; index < size; index++) {
        destroy_integer_queue(queues[index]);
    }
}
