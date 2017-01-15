/**
 * Recovers JPEGS from the memory card
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct
{
    BYTE buffer[512];
}jpeg;

int is_jpeg(jpeg imag)
{
   if (imag.buffer[0] == 0xff &&
           imag.buffer[1] == 0xd8 &&
           imag.buffer[2] == 0xff &&
           (imag.buffer[3] & 0xf0) == 0xe0)
        return 1;
        
    return 0;
}

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // forsenic image file
    char *image = argv[1];

    // open input file 
    FILE *inptr = fopen(image, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", image);
        return 2;
    }

    // temperory storage
    jpeg block;
    
    // keep track of images
    int num_of_imag = 0;
    
    // keep track of file ptr
    int num_of_bytes;
    
    // read until first jpeg reached
    num_of_bytes = fread(&block, 1, 512,inptr);
    while (!is_jpeg(block) && num_of_bytes == 512)
    {
        fread(&block, 1, 512,inptr);
    }
        
    // create jpegs until EOF is reached
    int new_jpeg = 1;
    char filename[10];
    FILE* img;
    while (num_of_bytes == 512)
    {
        if (new_jpeg == 1)
        {
            // open a file
            num_of_imag++;
            sprintf(filename, "%03i.jpg", num_of_imag);
            img = fopen(filename, "w");
            new_jpeg = 0;
        }
        
        // write into file
        fwrite(&block, 1, 512, img);
        
        // read next block
        num_of_bytes = fread(&block, 1, 512,inptr);
        if (is_jpeg(block))
        {
            new_jpeg = 1;
        }
    }

    // close infile
    fclose(inptr);


    // success
    return 0;
}
