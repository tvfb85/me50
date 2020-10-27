#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    BYTE *buffer = malloc(512 * sizeof(BYTE));
    FILE *img;
    char newfile[8];
    int count = 0;

    while (fread(buffer, sizeof(BYTE), 512, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!img)
            {
                sprintf(newfile, "%03i.jpg", count);
                img = fopen(newfile, "w");
                if (img == NULL)
                {
                    printf("Could not create image file\n");
                    return 1;
                }
                fwrite(buffer, sizeof(BYTE), 512, img);
                count++;
            }
            else
            {
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
            if (img != NULL)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }

    free(buffer);
}
