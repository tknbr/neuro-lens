#ifndef INTERNAL_IMG_IO_H
#define INTERNAL_IMG_IO_H

#include "../../include/img_utils.h" // Include the public API for type definitions
#include "internal_img_png.h"

// Function to load a PNG image
Image* img_io_load(const char *filename);

// Function to write a PNG image
void img_io_write(const char *filename, Image *img);

#endif // INTERNAL_IMG_IO_H