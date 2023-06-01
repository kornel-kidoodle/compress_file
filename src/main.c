/*
 * Main program for run-length encoding.
 */
#include "./include/encoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void *safe_calloc(size_t count, size_t size)
{
    void *p = calloc(count, size);
    if (p == NULL)
        terminate("Error: Memory allocation failed.\n");
    return p;
}

int main(int argc, char *argv[])
{   
    const char *ext = "rle", *search;
    char *new_file;
    bool decompress = false;
    int argc_file = 1;

    if (argc < 2 || argc > 3)
        terminate("Usage: compress_file [OPTION] [FILE]\n");

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0) {
            decompress = true;
            argc_file = (i == 1) ? 2 : 1;
            break;
        }
    }

    if (decompress) {
        if ((search = strrchr(argv[argc_file], '.')) == NULL || strstr(search, ext) == NULL) {
            printf("Input file must have extension'%s'\n", ext);
            exit(EXIT_FAILURE);
        }
        new_file = safe_calloc(strlen(argv[argc_file]) - strlen(ext), sizeof(char));
        strncpy(new_file, argv[argc_file], search - argv[argc_file]);
        run_length_decoder(argv[argc_file], new_file);
    }
    else {
        new_file = safe_calloc(strlen(argv[1]) + 5, sizeof(char));
        strcat(strcpy(new_file, argv[1]), ".rle");
        run_length_encoder(argv[1], new_file);
    }

    return 0;
}
