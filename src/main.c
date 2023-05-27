/*
 * Main program for run-length encoding.
 */
#include "./include/encoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{   
    FILE *fp_in, *fp_out;

    if (argc != 2)
        terminate("Usage: compress_file filename\n");

    if ((fp_in = fopen(argv[1], "rb")) == NULL)
        terminate("Input file can't be opened.\n");

    char new_file[strlen(argv[1]) + 5];
    strcat(strcpy(new_file, argv[1]), ".rle");

    if ((fp_out = fopen(new_file, "wb")) == NULL)
        terminate("Output file can't be opened.\n");

    run_length_encoder(fp_in, fp_out);
    
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}
