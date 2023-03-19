#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Checks for proper usage
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Opens file
    FILE *raw = fopen(argv[1], "rb");

    // Checks if file could not be opened
    if (raw == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Some starting vars
    int img_count = 0;
    BYTE buffer[BLOCK_SIZE];
    BYTE signature[4] = {255, 216, 255, 224};
    char filename[8];
    FILE *out = NULL;

    // Reads one block at a time till end of file
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw) != 0)
    {
        // Checks for jpeg signature
        bool jpeg = buffer[0] == signature[0] && buffer[1] == signature[1] && buffer[2] == signature[2] && (buffer[3] >= signature[3]
                    && buffer[3] <= 239);

        if (jpeg)
        {
            // Closes previous file if any
            if (out != NULL)
            {
                fclose(out);
            }

            // Opens new file to append
            sprintf(filename, "%03d.jpg", img_count);
            out = fopen(filename, "ab");
            img_count++;
        }

        // Checks if there is a file to append to
        if (out == NULL)
        {
            continue;
        }
        else if (out != NULL)
        {
            // Append all of buffer into file
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, out);
        }
    }

    fclose(raw);
    fclose(out);

    // Successful execution
    return 0;
}