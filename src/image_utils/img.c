/**
 * General Image, we will always work with this type
 * 
 */
#include <stdlib.h>
#include <string.h>

#include "../../include/img_utils.h"
#include "../../internal/image_utils/internal_img_io.h"


Image* img_new(int width, int height)
{
	Image *image = (Image *)malloc(sizeof(Image));
	if (!image) return NULL; // Error during malloc

	image->width = width;
    image->height = height;

    image->pixels = (pixel *)malloc(sizeof(pixel) * image->width * image->height);

    if (!image->pixels) return NULL; // Error during malloc

    return image;
}

void img_free(Image* img)
{
	if (img != NULL) {
        free(img->pixels); // Free the pixels array
        free(img);         // Then free the image struct itself
    }
}

// Nearest-neighbor image resize function, on succes return 0, else 1
int img_resize(Image** src, int new_width, int new_height) {
    if (!src || !*src) return 1; // Check for valid source image

    Image* resized = img_new(new_width, new_height); // Create new resized image
    if (!resized) return 1; // Check for successful allocation

    // Using fixed-point arithmetic with a scale factor of 1024 for precision
    int scaleX = ((*src)->width << 10) / new_width;
    int scaleY = ((*src)->height << 10) / new_height;

    int srcY = 0;
    for (int y = 0; y < new_height; y++, srcY += scaleY) {
        int srcX = 0;
        for (int x = 0; x < new_width; x++, srcX += scaleX) {
            // Accessing source pixel based on scaled indices
            pixel* srcPixel = &(*src)->pixels[(srcY >> 10) * (*src)->width + (srcX >> 10)];
            pixel* dstPixel = &resized->pixels[y * new_width + x];
            *dstPixel = *srcPixel;
        }
    }

    img_free(*src); // Free the original image
    *src = resized; // Update the source image pointer to point to the resized image
    return 0;
}

// Crop image function
int img_crop(Image **src, int x, int y, int width, int height) {
    if (!src || !*src) return 1;

    Image* cropped = img_new(width, height);
    if (!cropped) return 1; // Allocation failure


    for (int newY = 0; newY < height; newY++) {
        for (int newX = 0; newX < width; newX++) {
            //  Accessing source pixel based on scaled indices
            pixel *srcPixel = &(*src)->pixels[((y + newY) * (*src)->width + x + newX)];
            pixel *dstPixel = &cropped->pixels[newY * width + newX];
            *dstPixel = *srcPixel;
        }
    }

    // Free the original image and update the pointer to point to the cropped image
    img_free(*src);
    *src = cropped;

    return 0; // Success
}

Image* img_load(const char *filename)
{
    return img_io_load(filename);
}

void img_write(const char *filename, Image *img)
{
    img_io_write(filename, img);
}