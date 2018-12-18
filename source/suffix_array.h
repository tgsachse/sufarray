// Header file for an integer queue.
// Written by Tiger Sachse.

#include <stdlib.h>
#include <limits.h>

#define PADDING 10
#define ALPHABET_SIZE 26

// Signal flags for functions.
typedef enum flag {
    FLAG_FAILURE=INT_MIN,
    FLAG_SUCCESS,
    FLAG_STRING_LOWER,
    FLAG_PATTERN_LOWER
} flag;

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

// Functional prototypes for integer queues.
integer_queue* new_integer_queue(void);
integer_queue_node* new_integer_queue_node(int);
int is_empty(integer_queue*);
flag enqueue(integer_queue*, int);
int dequeue(integer_queue*);
void print_integer_queue(integer_queue*);
void destroy_integer_queue(integer_queue*);
void destroy_integer_queues(integer_queue**, int);

// Functional prototypes for suffix arrays.
int index_of_character(char);
int is_alphabetic(char);
flag contains(char*, char*);
suffix_array* new_suffix_array(char*);
flag sort_suffixes_alphabetically(suffix_array*);
int search(suffix_array*, char*);
void print_unsorted_suffixes(suffix_array*);
void print_sorted_suffixes(suffix_array*);
void print_highlighted_substring(suffix_array*, int, int);
void destroy_suffix_array(suffix_array*);
