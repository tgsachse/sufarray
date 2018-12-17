// Driver program that takes a file input and creates a suffix array.
// Written by Tiger Sachse.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffix_array.h"

// Read a file into a dynamic character array.
char* read_file(char* file_name) {
    FILE* file;
    char buffer;
    char* string;
    int characters;
    int string_index;

    // Attempt to open the file.
    if ((file = fopen(file_name, "r")) == NULL) {
        return NULL;
    }
    
    // Count the number of valid characters in the file.
    characters = 0;
    while (fscanf(file, "%c", &buffer) != EOF) {
        if (is_alphabetic(buffer)) {
            characters++;
        }
    }

    // Allocate a character array to hold the valid characters.
    if ((string = malloc(sizeof(char) * (characters + 1))) == NULL) {
        fclose(file);

        return NULL;
    }

    // Go back to the beginning for more fun!
    rewind(file);

    // Save all valid characters from the file in the new character array.
    string_index = 0;
    while (fscanf(file, "%c", &buffer) != EOF) {
        if (is_alphabetic(buffer)) {
            string[string_index] = buffer;        
            string_index++;
        }
    }

    // All good things must come to an end.
    string[string_index] = '\0';

    fclose(file);

    return string;
}

// Main entry point of the program.
int main(int argument_count, char** arguments) {
    int position;
    int argument;
    char* string;
    suffix_array* array;

    // Yell at the user if they are missing arguments.
    if (argument_count < 2) {
        printf("First argument after --run must be a string or file.\n");
        printf("All arguments afterwards will be treated as search patterns.\n");

        return -1;
    }

    // Attempt to use the first argument as a file name. If this fails,
    // create a suffix array using the first argument as a string.
    if ((string = read_file(arguments[1])) == NULL) {
        if ((array = new_suffix_array(arguments[1])) == NULL) {
            printf(
                "Something went wrong while creating the suffix array from '%s'!\n",
                arguments[1]
            );

            return -1;
        }
    }

    // The first argument was a file name. Use the new, sanitized string
    // to create a suffix array.
    else {
        if ((array = new_suffix_array(string)) == NULL) {
            printf(
                "Something went wrong while creating the suffix array from '%s'!\n",
                string
            );

            return -1;
        }
    }

    // Print the unsorted and sorted suffixes.
    printf("Unsorted suffixes:\n");
    print_unsorted_suffixes(array);
    printf("\n");
    printf("Sorted suffixes:\n");
    print_sorted_suffixes(array);
    printf("\n");

    // Run a search for all of the rest of the arguments.
    for (argument = 2; argument < argument_count; argument++) {
        printf("Searching for '%s': ", arguments[argument]);
        if ((position = search(array, arguments[argument])) == FLAG_FAILURE) {
            printf("not found!\n");
        }
        else {
            printf("found at position %d!\n", position);
            print_highlighted_substring(array, position, strlen(arguments[argument]));
            printf("\n");
        }
    }

    free(string);
    destroy_suffix_array(array);

    return 0;
}
