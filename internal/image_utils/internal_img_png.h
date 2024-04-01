#ifndef INTERNAL_IMG_PNG_H
#define INTERNAL_IMG_PNG_H

#include "../../include/img_utils.h" // Include the public API for type definitions

void img_png_write(const char *filename, Image *img);

Image* img_png_open(FILE *fp);

#endif // INTERNAL_IMG_PNG_H