#include <stdlib.h>
#include <stdio.h>

#include "../../include/image_utils.h"


// Function to load a PNG image
Image* load_png_image(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL; // File could not be opened

    // Initialize read structure
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) return NULL; // Read structure not created

    // Initialize info structure
    png_infop info = png_create_info_struct(png);
    if (!info) return NULL; // Info structure not created

    if (setjmp(png_jmpbuf(png))) return NULL; // Error during init_io

    png_init_io(png, fp);
    png_read_info(png, info);

    Image *image = (Image *)malloc(sizeof(Image));
    image->width = png_get_image_width(png, info);
    image->height = png_get_image_height(png, info);
    image->color_type = png_get_color_type(png, info);
    image->bit_depth = png_get_bit_depth(png, info);

    // Read file
    if (setjmp(png_jmpbuf(png))) return NULL; // Error during read_image

    image->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * image->height);
    for (int y = 0; y < image->height; y++) {
        image->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, image->row_pointers);

    fclose(fp);
    png_destroy_read_struct(&png, &info, NULL);

    return image;
}


// Function to save a PNG image
int save_png_image(const char *filename, Image *image) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return -1; // File could not be opened for writing

    // Initialize write structure
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) return -1; // Write structure not created

    // Initialize info structure
    png_infop info = png_create_info_struct(png);
    if (!info) return -1; // Info structure not created

    if (setjmp(png_jmpbuf(png))) return -1; // Error during writing bytes

    png_init_io(png, fp);

    // Write header
    if (setjmp(png_jmpbuf(png))) return -1; // Error during writing header

    png_set_IHDR(png, info, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png, info);

    // Write bytes
    if (setjmp(png_jmpbuf(png))) return -1; // Error during writing bytes

    png_write_image(png, image->row_pointers);

    // End write
    if (setjmp(png_jmpbuf(png))) return -1; // Error during end of write

    png_write_end(png, NULL);

    fclose(fp);
    png_destroy_write_struct(&png, &info);

    return 0; // Success
}


// Function to free the memory allocated for an Image
void free_image(Image *image) {
    if (image != NULL) {
        // Free each row
        if (image->row_pointers != NULL) {
            for (int y = 0; y < image->height; y++) {
                free(image->row_pointers[y]);
            }
            // Free the array of row pointers
            free(image->row_pointers);
        }
        // Finally, free the image structure itself
        free(image);
    }
}