#include "./include/encoder.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS 8

int count_bytes(int i)
{
    int count = 0;
    while (i > 0) {
        i >>= BITS;
        count++;
    }
    return count;
}

void write_bytes(FILE *fp_out, BYTE *byte, int count)
{
    BYTE byte_count = 0;
    int num_bytes = count_bytes(count);

    for (int i = 0; i < num_bytes; i++) {
        byte_count |= (count >> (i * BITS)) & 0xFF;
        if (putc(byte_count, fp_out) == EOF)
            terminate("Error writing byte.\n");
    }
    if (putc(*byte, fp_out) == EOF)
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
