// Header file for an integer queue.
// Written by Tiger Sachse.

#include <stdlib.h>
#include <limits.h>

#define ALPHABET_SIZE 26
#define OPERATION_FAILURE INT_MIN
#define OPERATION_SUCCESS INT_MIN + 1

// A node in the integer queue linked list.
typedef struct integer_queue_node {
    int data;
    struct integer_queue_node* next;
} integer_queue_node;

// An integer queue that tracks the beginning and end of a linked list.
typedef struct integer_queue {
    integer_queue_node* head;
    integer_queue_node* tail;
} integer_queue;

// A suffix array that holds a copy of the original string.
typedef struct suffix_array {
    char* string;
    int* suffixes;
    int string_length;
} suffix_array;

// Functional prototypes
integer_queue* new_integer_queue(void);
integer_queue_node* new_integer_queue_node(int);
int is_empty(integer_queue*);
int enqueue(integer_queue*, int);
int dequeue(integer_queue*);
void print_integer_queue(integer_queue*);
void destroy_integer_queue(integer_queue*);
void destroy_integer_queues(integer_queue**, int);

int index_of_character(char);
int is_alphabetic(char);
suffix_array* new_suffix_array(char*);
int sort_suffixes_alphabetically(suffix_array*);
void print_suffix_array(suffix_array*);
void print_suffixes(suffix_array*);
void destroy_suffix_array(suffix_array*);
