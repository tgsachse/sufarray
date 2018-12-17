// Provides a suffix array that contains a copy of a string and that
// string's suffixes, sorted in alphabetical order.
// Written by Tiger Sachse.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffix_array.h"

// Get the index of a character in an array, based on its position in the Latin alphabet.
int index_of_character(char character) {
    if (character >= 'A' && character <= 'Z') {
        return character - 'A';
    }
    else if (character >= 'a' && character <= 'z') {
        return character - 'a';
    }
    else {
        return OPERATION_FAILURE;
    }
}

// Determine if the character is an alphabetic character.
int is_alphabetic(char character) {
    return (
        (character >= 'A' && character <= 'Z')
        || (character >= 'a' && character <= 'z')
    );
}

// Create a new suffix array and sort the suffixes.
suffix_array* new_suffix_array(char* string) {
    int characters;
    int suffix_index;
    suffix_array* array;

    // If the string contains nothing, create nothing.
    if (string == NULL || string[0] == '\0') {
        return NULL;
    }

    // Ensure that all characters are alphabetic and count the number of characters.
    // No non-alphabetic characters are allowed in this implementation of suffix arrays.
    characters = 0;
    while (string[characters] != '\0') {
        if (!is_alphabetic(string[characters])) {
            return NULL;
        }
        else {
            characters++;
        }
    }

    // Create the suffix array container struct.
    if ((array = malloc(sizeof(suffix_array))) == NULL) {
        return NULL;
    }

    // Create a character array to store a copy of the string. Don't forget
    // an extra cell for the null terminator!
    if ((array->string = malloc(sizeof(char) * (characters + 1))) == NULL) {
        destroy_suffix_array(array);

        return NULL;
    }

    // Create the suffix position integer array.
    if ((array->suffixes = malloc(sizeof(int) * characters)) == NULL) {
        destroy_suffix_array(array);

        return NULL;
    }

    // Copy the string into the container struct. Also save the string length
    // and initialize all suffix positions in the suffix array to their respective
    // start position in the string. These suffix positions are not alphabetically
    // sorted. That step is next!
    strcpy(array->string, string);
    array->string_length = characters;
    for (suffix_index = 0; suffix_index < array->string_length; suffix_index++) {
        array->suffixes[suffix_index] = suffix_index;
    }

    // Sort the suffix positions in the suffix array alphabetically.
    if (sort_suffixes_alphabetically(array) == OPERATION_FAILURE) {
        destroy_suffix_array(array);

        return NULL;
    }

    return array;
}

// Use radix sort to sort the suffixes in a suffix array alphabetically.
int sort_suffixes_alphabetically(suffix_array* array) {
    int offset;
    int result;
    int queue_index;
    int char_target;
    int suffix_index;
    integer_queue* unsorted_queue;
    integer_queue* queues[ALPHABET_SIZE];

    // Ensure that the suffix array exists.
    if (array == NULL) {
        return OPERATION_FAILURE;
    }

    // Create an unsorted queue for suffixes that do not have enough characters
    // to be sorted on any particular run of radix sort.
    if ((unsorted_queue = new_integer_queue()) == NULL) {
        return OPERATION_FAILURE;
    }

    // Create ALPHABET_SIZE integer queues in an array for radix sort.
    for (queue_index = 0; queue_index < ALPHABET_SIZE; queue_index++) {

        // If a call to create a new queue fails, free all
        // previously created queues and fail.
        if ((queues[queue_index] = new_integer_queue()) == NULL) {
            destroy_integer_queues(queues, ALPHABET_SIZE);
            destroy_integer_queue(unsorted_queue);

            return OPERATION_FAILURE;
        }
    }

    // Perform radix sort on all suffixes, using the least significant character
    // first. The target character of the current run is determined by the offset.
    // If the offset is too big for a particular suffix, that suffix is sent to the
    // unsorted queue for that round of radix sort. This mechanism is similar to what
    // happens when attempting to sort numbers of different lengths (e.g. 99 and 5577)
    // in regular radix sort.
    offset = array->string_length - 1;
    while (offset >= 0) {

        // For each suffix: if the offset is too big, place that suffix in the
        // unsorted queue, otherwise placee the suffix in the appropriate queue that
        // corresponds to that suffix's offset character.
        for (suffix_index = 0; suffix_index < array->string_length; suffix_index++) {
            char_target = array->suffixes[suffix_index] + offset;
            if (char_target >= array->string_length) {

                // Attempt to enqueue into the unsorted queue. If enqueuing fails,
                // destroy all the queues and return failure.
                result = enqueue(unsorted_queue, array->suffixes[suffix_index]);
                if (result == OPERATION_FAILURE) {
                    destroy_integer_queues(queues, ALPHABET_SIZE);
                    destroy_integer_queue(unsorted_queue);

                    return OPERATION_FAILURE;
                }
            }
            else {
                // Attempt to enqueue into the appropriate sorted queue. If
                // enqueuing fails, destroy all the queues and return failure.
                result = enqueue(
                    queues[index_of_character(array->string[char_target])],
                    array->suffixes[suffix_index]
                );
                if (result == OPERATION_FAILURE) {
                    destroy_integer_queues(queues, ALPHABET_SIZE);
                    destroy_integer_queue(unsorted_queue);

                    return OPERATION_FAILURE;
                }
            }
        }

        // Dequeue all contents of the unsorted queue back into the suffixes
        // array, in order.
        suffix_index = 0;
        while (!is_empty(unsorted_queue)) {
            array->suffixes[suffix_index] = dequeue(unsorted_queue);
            suffix_index++;
        }

        // Dequeue all contents from the sorted queues back into the suffixes
        // array, in order.
        for (queue_index = 0; queue_index < ALPHABET_SIZE; queue_index++) {
            while(!is_empty(queues[queue_index])) {
                array->suffixes[suffix_index] = dequeue(queues[queue_index]);
                suffix_index++;
            }
        }

        // Decrease the offset to move to the next, more significant, character.
        offset--;
    }

    // Clean up after yourself!
    destroy_integer_queue(unsorted_queue);
    destroy_integer_queues(queues, ALPHABET_SIZE);
}

// Print the unsorted suffixes in a suffix array.
void print_unsorted_suffixes(suffix_array* array) {
    int suffix_offset;

    // Nothing to do!
    if (array == NULL) {
        printf("Suffix array is NULL!\n");

        return;
    }

    // Obtain the starting position of each suffix string by offsetting
    // the base pointer of the string with the suffix_offset.
    for (suffix_offset = 0; suffix_offset < array->string_length; suffix_offset++) {
        printf("%s\n", array->string + suffix_offset);
    }
}

// Print the alphabetized suffixes in a suffix array.
void print_sorted_suffixes(suffix_array* array) {
    int suffix_index;

    // Nothing to do! It is safe to assume that if the array is not
    // NULL then it will have a string of length >= 1. This is due to
    // the new_suffix_array() function only executing with strings of
    // length >= 1.
    if (array == NULL) {
        printf("Suffix array is NULL!\n");

        return;
    }
   
    // Obtain the starting position of each suffix string by offsetting
    // the base pointer of the string with the appropriate offset found
    // in array->suffixes.
    for (suffix_index = 0; suffix_index < array->string_length; suffix_index++) {
        printf("%s\n", array->string + array->suffixes[suffix_index]);
    }
}

// Destroy a suffix array.
void destroy_suffix_array(suffix_array* array) {

    // Nothing to do!
    if (array == NULL) {
        return;
    }

    free(array->suffixes);
    free(array->string);
    free(array);
}
