#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>

typedef char BYTE;

/* Function prototypes */

/* Encodes the input file using run-length encoding. */
void run_length_encoder(char *filename_in, char *filename_out);

/* Decodes the input file using run-length decoding. */
void run_length_decoder(char *filename_in, char *filename_out);

/* Writes the byte and its count to the output file. */
void write_bytes(FILE *fp_out, BYTE *byte, int count);

/* Prints an error message and terminates the program. */
void terminate(const char *message);

#endif
