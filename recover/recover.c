/**
 * Recovers JPEGS from the memory card
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct
{
    BYTE arr[512];
}jpeg;


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

   
  

    // close infile
    fclose(inptr);


    // success
    return 0;
}
