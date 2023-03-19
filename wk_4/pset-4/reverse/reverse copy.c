#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse [input.wav] [output.wav]\n");
        return 1;
    }


    // Open input file for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Read header into an array
    WAVHEADER head;
    fread(&head, sizeof(head), 1, infile);

    // Use check_format to ensure WAV format
    if (check_format(head) != 0)
    {
        printf("Incorrect file format detected\n");
        return 2;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Unable to open/create output file\n");
        return 1;
    }

    // Write header to file
    fwrite(&head, sizeof(head), 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(head);

    // Write reversed audio to file
    // TODO #8
    fseek(infile, block_size, SEEK_END);

    while(ftell(infile) - block_size > sizeof(head))
    {
        fseek(infile, -2 * block_size, SEEK_CUR);
        printf("%li, ", ftell(infile));
        BYTE c[block_size];
        fread(&c, block_size, 1, infile);
        fwrite(&c, block_size, 1, output);
        printf("%li\n", ftell(infile));
    }


    // Close opened files
    fclose(infile);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    int block_size = header.numChannels * header.bitsPerSample/8;
    return block_size;
}