// Provides a suffix array for general use.
// Written by Tiger Sachse.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffix_array.h"

// Get the index of a character in an array, based on its position in the alphabet.
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

// Return if the character is an alphabetic character.
int is_alphabetic(char character) {
    return ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'));
}

// Create a new suffix array with suffixes alphabetically sorted.
suffix_array* new_suffix_array(char* string) {
    int index;
    suffix_array* array;

    if (string == NULL || string[0] == '\0') {
        return NULL;
    }

    // Ensure that all characters are alphabetic and count the number of characters.
    index = 0;
    while (string[index] != '\0') {
        if (!is_alphabetic(string[index])) {
            return NULL;
        }
        else {
            index++;
        }
    }

    // Create the holding struct and the appropriate arrays in memory.
    if ((array = malloc(sizeof(suffix_array))) == NULL) {
        return NULL;
    }

    if ((array->string = malloc(sizeof(char) * (index + 1))) == NULL) {
        destroy_suffix_array(array);

        return NULL;
    }

    if ((array->suffixes = malloc(sizeof(int) * index)) == NULL) {
        destroy_suffix_array(array);

        return NULL;
    }

    // Copy the string into the holding struct. Also save the string length
    // and initialize all suffixes in the suffix array to their respective
    // position in the string.
    strcpy(array->string, string);
    array->string_length = index;
    for (index = 0; index < array->string_length; index++) {
        array->suffixes[index] = index;
    }

    return array;
}

// Use radix sort to sort the suffixes in a suffix array alphabetically.
int sort_suffixes_alphabetically(suffix_array* array) {
    int index;
    integer_queue* queues[ALPHABET_SIZE];

    // Ensure that the suffix array exists.
    if (array == NULL) {
        return OPERATION_FAILURE;
    }

    // Create ALPHABET_SIZE integer queues in an array for radix sort!
    for (index = 0; index < ALPHABET_SIZE; index++) {

        // If a call to create a new queue fails, free all
        // previously created queues and fail.
        if ((queues[index] = new_integer_queue()) == NULL) {
            destroy_integer_queues(queues, ALPHABET_SIZE);

            return OPERATION_FAILURE;
        }
    }


    destroy_integer_queues(queues, ALPHABET_SIZE);
}

// Print the contents of the suffix array.
void print_suffix_array(suffix_array* array) {
    int index;

    if (array == NULL) {
        printf("Suffix array is NULL!\n");

        return;
    }

    printf("String: %s\n", array->string);
    printf("String length: %d\n", array->string_length);
    printf("Suffixes: ");
    for (index = 0; index < array->string_length; index++) {
        printf("%d%s", index, (index == array->string_length - 1) ? "\n" : " ");
    }
}

// Print the suffixes in a suffix array.
void print_suffixes(suffix_array* array) {
    int index;

    if (array == NULL) {
        printf("Suffix array is NULL!\n");

        return;
    }
   
    // Print each suffix by offsetting the base pointer of the string.
    for (index = 0; index < array->string_length; index++) {
        printf("%s\n", array->string + array->suffixes[index]);
    }
}

// Destroy the provided suffix array.
void destroy_suffix_array(suffix_array* array) {
    if (array == NULL) {
        return;
    }

    free(array->string);
    free(array->suffixes);
    free(array);
}

