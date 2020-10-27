#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Setup alias for 8-bit unsigned integer
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure command-line argument has been given
    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    // Open the file with read-only flag
    FILE *file = fopen(argv[1], "r");

    // Check file was opened successfully, otherwise return error status
    if (file == NULL)
    {
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    // Dynamically allocate memory for buffer
    BYTE *buffer = malloc(512 * sizeof(BYTE));

    // Setup variable of type FILE to write to
    FILE *img;

    // Setup variable with enough bytes to hold filename
    char newfile[8];

    // Initialize counter to zero
    int count = 0;

    // Read the file to buffer in 512 byte chunks
    while (fread(buffer, sizeof(BYTE), 512, file))
    {
        // Use first four bytes to identify jpeg images
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If an image doesn't already exist
            if (!img)
            {
                // Format filename using count variable
                sprintf(newfile, "%03i.jpg", count);

                // Open file with write capabilities
                img = fopen(newfile, "w");

                // Ensure newfile is not null before being written to
                if (img == NULL)
                {
                    printf("Could not create image file\n");
                    return 1;
                }

                // Write data in 512-byte chunks from buffer to new file
                fwrite(buffer, sizeof(BYTE), 512, img);

                // Increment count of jpegs found
                count++;
            }
            else
            {
                // Close the existing file before opening and writing to newfile
                fclose(img);

                sprintf(newfile, "%03i.jpg", count);

                img = fopen(newfile, "w");

                if (img == NULL)
                {
                    return 1;
                }

                fwrite(buffer, sizeof(BYTE), 512, img);

                count++;
            }
        }
        else
        {
            // If an new img file exists, continue to write from the buffer to the file
            if (img != NULL)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }

    // Prevent memory leak
    free(buffer);
}
