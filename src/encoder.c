#include "./include/encoder.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS 8
#define MAX_BYTE_SIZE 0xFF


void write_bytes(FILE *fp_out, BYTE *byte, int count)
{
    for (; count >= MAX_BYTE_SIZE; count -= MAX_BYTE_SIZE) {
        if (putc(MAX_BYTE_SIZE, fp_out) == EOF)
            terminate("Error writing byte.\n");
    }
    if (putc(count, fp_out) == EOF || putc(*byte, fp_out) == EOF)
        terminate("Error writing byte.\n");
}

void run_length_encoder(FILE *fp_in, FILE *fp_out)
{
    BYTE byte1, byte2 = '\0';
    int count = 1;

    while ((byte1 = fgetc(fp_in)) != EOF) {
        if (byte1 == byte2)
            count++;
        else {
            write_bytes(fp_out, &byte2, count);
            count = 1;
        }
        byte2 = byte1;
    }
    write_bytes(fp_out, &byte2, count);
}

void terminate(const char *message)
{
    printf("%s", message);
    exit(EXIT_FAILURE);
}
