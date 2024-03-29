// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t *fheader = malloc(HEADER_SIZE);

    if (fheader == NULL)
    {
        printf("Could not allocate memory\n");
        return 1;
    }

    fread(fheader, HEADER_SIZE, 1, input);

    fwrite(fheader, HEADER_SIZE, 1, output);
    free(fheader);

    // Read rsamples from input file and write updated data to output file
    int16_t buffer;

    int nmemb = sizeof(int16_t);

    while (fread(&buffer, nmemb, 1, input))
    {
        buffer = buffer * factor;

        fwrite(&buffer, nmemb, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
