#include <stdlib.h>

#include "../../internal/img_utils/internal_img_png.h"


Image* img_png_open(FILE *fp)
{

	// Initialize read structure
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) return NULL; // Read structure not created

    // Initialize info structure
    png_infop info = png_create_info_struct(png);
    if (!info) return NULL; // Info structure not created

    // Read file
    if (setjmp(png_jmpbuf(png))) return NULL; // Error during init_io

    png_init_io(png, fp);
    png_read_info(png, info);

    png_byte color_type = png_get_color_type(png, info);

    if (color_type != PNG_COLOR_TYPE_RGBA)
    {
        printf("color type not supported\n");
        return NULL;
    }

    Image *image = img_new(png_get_image_width(png, info), png_get_image_height(png, info));

    if (!image) return NULL; // Not enough img space

    // Set up row pointers directly in the allocated pixels array
    png_bytep row_pointers[image->height];
    for (int y = 0; y < image->height; y++) {
        row_pointers[y] = (png_bytep)(image->pixels + y * image->width);
    }

    png_read_image(png, row_pointers);
    png_destroy_read_struct(&png, &info, NULL);

    return image;
}


void img_png_write(const char *filename, Image *img)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Could not open file %s for writing.\n", filename);
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        fprintf(stderr, "Could not allocate write struct.\n");
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        fclose(fp);
        png_destroy_write_struct(&png, NULL);
        fprintf(stderr, "Could not allocate info struct.\n");
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        fclose(fp);
        png_destroy_write_struct(&png, &info);
        fprintf(stderr, "Error during PNG creation.\n");
        return;
    }

    png_init_io(png, fp);

    // Assuming the image struct holds 8-bit per channel RGB images
    png_set_IHDR(png, info, img->width, img->height, 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // Convert the pixels array to row pointers
    png_bytep row_pointers[img->height];
    for (int y = 0; y < img->height; y++) {
        row_pointers[y] = (png_bytep) &img->pixels[y * img->width];
    }

    png_set_rows(png, info, row_pointers);
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);

    fclose(fp);
    png_destroy_write_struct(&png, &info);
}
