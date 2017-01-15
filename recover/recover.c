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
    
    // read until end of file is reached
    while (fread(&block, 1, 512,inptr) == 512)
    {
        
    }

    // close infile
    fclose(inptr);


    // success
    return 0;
}
