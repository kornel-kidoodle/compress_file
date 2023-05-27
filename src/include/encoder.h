#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>

typedef char BYTE;

/* Function prototypes */

/* Counts the number of bytes needed to represent an integer. */
int count_bytes(int i);

/* Encodes the input file using run-length encoding. */
void run_length_encoder(FILE *fp_in, FILE *fp_out);

/* Writes the byte and its count to the output file. */
void write_bytes(FILE *fp_out, BYTE *byte, int count);

/* Prints an error message and terminates the program. */
void terminate(const char *message);

#endif
