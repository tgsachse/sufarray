// Implementation of an integer queue.
// Written by Tiger Sachse.

#include <stdio.h>
#include <stdlib.h>
#include "suffix_array.h"

// Create a new holding struct for an integer queue.
integer_queue* new_integer_queue(void) {
    return calloc(1, sizeof(integer_queue));
}

// Create a new node for an integer queue.
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

// Return if the queue is empty.
int is_empty(integer_queue* queue) {
    return (queue == NULL || queue->head == NULL || queue->tail == NULL);
}

// Add a new integer to the queue.
int enqueue(integer_queue* queue, int data) {

    // Can't enqueue into a non-existent queue.
    if (queue == NULL) {
        return OPERATION_FAILURE;
    }

    // If the queue is empty, make a new node at the head of the queue.
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

// Remove data from the front of the queue.
int dequeue(integer_queue* queue) {
    int dequeued_data;
    integer_queue_node* dequeued_node;

    // Can't dequeue from an empty queue!
    if (is_empty(queue)) {
        return OPERATION_FAILURE;
    }

    // Save the dequeued node and advance the head pointer. If this
    // results in head being NULL, set tail to be NULL as well.
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

    // Free the holding struct too!
    free(queue);
}

// Destroy an array of integer queues.
void destroy_integer_queues(integer_queue** queues, int size) {
    int index;

    if (queues == NULL) {
        return;
    }

    for (index = 0; index < size; index++) {
        destroy_integer_queue(queues[index]);
    }
}
