#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *in = fopen(argv[1], "rb");

    if (in == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, in);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("%s is not a WAV file\n", argv[1]);
    }

    // Open output file for writing
    FILE *out = fopen(argv[2], "wb");

    if (out == NULL)
    {
        printf("Could not open %s\n", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, out);

    // Use get_block_size to calculate size of block
    int blocksize = get_block_size(header);

    // Buffer
    BYTE buffer[blocksize];
    int size = sizeof(WAVHEADER);

    // Moves pointer position to end for read
    fseek(in, blocksize, SEEK_END);

    // While the pointer position is not at the header
    while ((ftell(in) - blocksize) > size)
    {
        // Move the positionto read new block from back
        fseek(in, (-2 * blocksize), SEEK_CUR);

        // Performs read and write operation
        fread(buffer, sizeof(BYTE), blocksize, in);
        fwrite(buffer, sizeof(BYTE), blocksize, out);
    }

    // Closes files
    fclose(out);
    fclose(in);

    // successful execution
    return 0;
}

int check_format(WAVHEADER header)
{
    // Gets format
    BYTE format[4];

    for (int i = 0; i < 4; i++)
    {
        format[i] = header.format[i];
    }

    // Ensures format says WAVE
    if (format[0] == 87 && format[1] == 65 && format[2] == 86 && format[3] == 69 /*nice*/)
    {
        // It is a WAV file
        return 1;
    }

    // It is not a WAV file
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // Calculate block size
    int blocks = header.numChannels * (header.bitsPerSample / 8);

    // Block size
    return blocks;
}