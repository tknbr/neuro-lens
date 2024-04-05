#include <stdlib.h>
#include <stdio.h>

#include "../../internal/img_utils/internal_img_io.h"


// Function to load a PNG image
Image* img_io_load(const char *filename)
{
    
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL; // File could not be opened

    Image *image = img_png_open(fp);

    fclose(fp);

    return image;
}

void img_io_write(const char *filename, Image *img)
{
    img_png_write(filename, img);
}
