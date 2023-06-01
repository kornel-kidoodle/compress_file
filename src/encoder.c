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

void run_length_encoder(char *filename_in, char *filename_out)
{
    FILE *fp_in, *fp_out;
    BYTE byte1, byte2;
    int count = 1;
    
    if ((fp_in = fopen(filename_in, "rb")) == NULL)
        terminate("Input file can't be opened.\n");

    if ((fp_out = fopen(filename_out, "wb")) == NULL)
        terminate("Output file can't be opened.\n");

    byte2 = getc(fp_in);
    while ((byte1 = getc(fp_in)) != EOF) {
        if (byte1 == byte2)
            count++;
        else {
            write_bytes(fp_out, &byte2, count);
            count = 1;
        }
        byte2 = byte1;
    }
    write_bytes(fp_out, &byte2, count);

    fclose(fp_in);
    fclose(fp_out);
}

void run_length_decoder(char *filename_in, char *filename_out)
{   
    FILE *fp_in, *fp_out;
    int byte, count = 0;
    
    if ((fp_in = fopen(filename_in, "rb")) == NULL)
        terminate("Input file can't be opened.\n");

    if ((fp_out = fopen(filename_out, "wb")) == NULL)
        terminate("Output file can't be opened.\n");

    while ((byte = getc(fp_in)) != EOF) {
        for (; byte == MAX_BYTE_SIZE; ) {
            count += MAX_BYTE_SIZE;
            byte = getc(fp_in);
        }
        if (byte > 0)
            count += byte;

        if ((byte = getc(fp_in)) != EOF) {
            for (int i =0; i < count; i++) {
                if (putc((char) byte, fp_out) == EOF)
                    terminate("Error: could not write to file.\n");
                }
            }
        count = 0;
    }

    fclose(fp_in);
    fclose(fp_out);
}

void terminate(const char *message)
{
    printf("%s", message);
    exit(EXIT_FAILURE);
}
