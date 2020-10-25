#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        return 1;
    }

    BYTE buffer[512];
    int counter = 0;
    bool found_first_jpg = false;
    FILE *img;
    while (fread(buffer, 512, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8  && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!found_first_jpg)
                found_first_jpg = true;
            else
                fclose(img);
            
            char filename[8];
            sprintf(filename, "%03i.jpg", counter++);
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            
        }
       
        else if (found_first_jpg)
        {
            fwrite(buffer, 512, 1, img);
        }
            
            
    }
}
