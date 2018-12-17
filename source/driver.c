#include <stdio.h>
#include <stdlib.h>
#include "suffix_array.h"

void test_queue(void) {
    integer_queue* queue;

    queue = new_integer_queue();
    enqueue(queue, 9);
    enqueue(queue, 12);
    enqueue(queue, -22);
    enqueue(queue, 0);
    printf("is empty: %d\n", is_empty(queue));
    print_integer_queue(queue);
    dequeue(queue);
    dequeue(queue);
    enqueue(queue, 100);
    printf("is empty: %d\n", is_empty(queue));
    print_integer_queue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    printf("is empty: %d\n", is_empty(queue));
    print_integer_queue(queue);
    enqueue(queue, 22);
    printf("is empty: %d\n", is_empty(queue));
    print_integer_queue(queue);
    dequeue(queue);
    printf("is empty: %d\n", is_empty(queue));
    print_integer_queue(queue);

    destroy_integer_queue(queue);
}

void test_suffix_array(void) {
    suffix_array* array;

    array = new_suffix_array("Invalid string here");
    printf("Should be NULL: %p\n", array);

    array = new_suffix_array("Invalidstringhere2");
    printf("Should be NULL: %p\n", array);
    print_suffix_array(array);

    array = new_suffix_array("helloworld");
    print_suffix_array(array);
    print_suffixes(array);
   
    destroy_suffix_array(array);
}

int main(void) {

    test_suffix_array();
    //test_queue();

    return 0;
}
