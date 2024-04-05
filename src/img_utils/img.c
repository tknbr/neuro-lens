/**
 * General Image, we will always work with this type
 * 
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/img_utils.h"
#include "../../internal/math/math_utils.h"
#include "../../internal/img_utils/internal_img_io.h"


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
    return RET_SUCCESS;
}

// Crop image function
int img_crop(Image **src, int x, int y, int width, int height) {
    if (!src || !*src) return RET_FAIL;

    Image* cropped = img_new(width, height);
    if (!cropped) return RET_FAIL; // Allocation failure


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

    return RET_SUCCESS; // Success
}

// Function to flip an image horizontally
void img_flip_horizontal(Image* img)
{
    if (!img || !img->pixels) return; // Check for valid image

    int width = img->width;
    int height = img->height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            int oppositeX = width - 1 - x; // Find the opposite pixel in the same row

            // Calculate the indexes for the current pixel and its horizontal opposite
            int currentIndex = (y * width + x);
            int oppositeIndex = (y * width + oppositeX);

            // Swap the current pixel with its horizontal opposite
            pixel temp = img->pixels[currentIndex];
            img->pixels[currentIndex] = img->pixels[oppositeIndex];
            img->pixels[oppositeIndex] = temp;
        }
    }
}

int img_rotate(Image* img, float angle) {

    // Calculate the center of the image
    float centerX = img->width / 2.0;
    float centerY = img->height / 2.0;

    // Create a new image to store the rotated pixels
    Image* rotatedImg = img_new(img->width, img->height);

    if (rotatedImg == NULL)
    {
        return RET_FAIL;
    }

    // Initialize the rotated image pixels to a default value (e.g., transparent or black)
    memset(rotatedImg->pixels, 0, img->width * img->height * sizeof(pixel));

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            // Calculate the new position for each pixel
            float newX = cos_approx(angle) * (x - centerX) - sin_approx(angle) * (y - centerY) + centerX;
            float newY = sin_approx(angle) * (x - centerX) + cos_approx(angle) * (y - centerY) + centerY;

            // Check if the new position is within the bounds of the original image
            if (newX >= 0 && newX < img->width && newY >= 0 && newY < img->height) {
                // For simplicity, this does not include interpolation.
                // Directly assign the pixel value to the closest integer position.
                rotatedImg->pixels[(int)newY * img->width + (int)newX] = img->pixels[y * img->width + x];
            }
        }
    }

    // Replace the original image pixels with the rotated pixels
    memcpy(img->pixels, rotatedImg->pixels, img->width * img->height * sizeof(pixel));
    img_free(rotatedImg);

    return RET_SUCCESS;
}

Image* img_load(const char *filename)
{
    return img_io_load(filename);
}

void img_write(const char *filename, Image *img)
{
    img_io_write(filename, img);
}