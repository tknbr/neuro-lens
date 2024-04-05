/**
 * @file img_utils.h
 * Public API for image manipulation.
 *
 * This file defines the public interface for creating, manipulating, and
 * managing images. It supports basic operations such as creating new images,
 * loading images from files, writing images to files, and performing common
 * manipulations like resizing and cropping.
 */

#ifndef IMG_UTILS_H
#define IMG_UTILS_H

/**
 * Structure representing a pixel with Red, Green, Blue, and Alpha channels.
 * Each channel is 8 bits, supporting values from 0 to 255.
 */
typedef struct {
    unsigned char R; ///< Red channel (0-255)
    unsigned char G; ///< Green channel (0-255)
    unsigned char B; ///< Blue channel (0-255)
    unsigned char A; ///< Alpha channel (0-255) for transparency
} pixel;

/**
 * Structure representing an image, consisting of its dimensions (width and height)
 * and an array of pixels storing the image data.
 */
typedef struct {
    int width;     ///< Width of the image in pixels
    int height;    ///< Height of the image in pixels
    pixel *pixels; ///< Pointer to the array of pixel data
} Image;


/**
 * Enum to hold return values
 */
typedef enum {
	RET_SUCCESS = 0,
	RET_FAIL    = 1
} ret_types;


/**
 * Creates a new image with specified dimensions.
 *
 * Allocates memory for a new Image structure and initializes its dimensions and
 * pixel data to default values. The caller is responsible for freeing the
 * allocated Image using img_free().
 *
 * @param width The width of the new image.
 * @param height The height of the new image.
 * @return A pointer to the newly created Image, or NULL if memory allocation fails.
 */
Image* img_new(int width, int height);

/**
 * Frees the memory allocated for an Image structure.
 *
 * This function should be called to free the memory associated with an Image
 * when it is no longer needed.
 *
 * @param img The Image to be freed.
 */
void img_free(Image* img);

/**
 * Resizes an image to new dimensions.
 *
 * Modifies the size of an image in place. The original image data is replaced
 * with a resized version. The resizing operation attempts to preserve the
 * aspect ratio and appearance of the original image as closely as possible.
 *
 * @param src A pointer to the pointer of the Image to be resized.
 * @param new_width The new width for the image.
 * @param new_height The new height for the image.
 * @return RET_SUCCESS on success, or RET_FAIL if an error occurs.
 */
int img_resize(Image** src, int new_width, int new_height);

/**
 * Crops an image to a specified rectangular area.
 *
 * Modifies the image in place to retain only the specified rectangular area.
 * The original image outside the specified area is discarded.
 *
 * @param src A pointer to the pointer of the Image to be cropped.
 * @param x The X coordinate of the top-left corner of the crop area.
 * @param y The Y coordinate of the top-left corner of the crop area.
 * @param width The width of the crop area.
 * @param height The height of the crop area.
 * @return RET_SUCCESS on success, or RET_FAIL if an error occurs.
 */
int img_crop(Image **src, int x, int y, int width, int height);

/**
 * Loads an image from a file.
 *
 * This function determines the format of the image file and loads it into a
 * new Image structure. The supported formats depend on the internal capabilities
 * of the library.
 *
 * @param filename The path to the image file to be loaded.
 * @return A pointer to the newly loaded Image, or NULL if loading fails.
 */
Image* img_load(const char *filename);

/**
 * Writes an image to a file.
 *
 * Saves the image data to a file in a specified format. The format is determined
 * by the file extension or can be specified in another way by the library's
 * internal implementation.
 *
 * @param filename The path to the file where the image will be saved.
 * @param img The Image to be saved.
 */
void img_write(const char *filename, Image *img);

/**
 * Flips an image horizontally in place.
 *
 * This function mirrors the image along its vertical axis, effectively reversing
 * the order of pixels in each row. The transformation is performed directly on the
 * input image data, modifying the original image.
 *
 * @param img A pointer to an Image structure representing the image to be flipped.
 *            The Image structure must be valid and contain allocated pixel data.
 *            If the Image pointer is NULL or contains no pixel data, the function
 *            will exit without performing any operations.
 */
void img_flip_horizontal(Image* img);

/**
 * Rotates an image by a given angle around its center.
 *
 * This function rotates an image clockwise by the specified angle in degrees, with the rotation
 * centered around the geometric center of the image. The rotated image replaces the original
 * image data. For simplicity, this implementation does not perform interpolation, which means
 * the quality of the rotated image may decrease, especially for angles that are not multiples
 * of 90 degrees.
 *
 * @param img A pointer to an Image structure representing the image to be rotated. The image
 *           must be valid and contain allocated pixel data.
 * @param angle The angle in degrees by which to rotate the image clockwise. The function uses
 *             an approximation of sine and cosine functions (`sin_approx` and `cos_approx`)
 *             to calculate the rotation, which may affect precision for large angles or require
 *             adjustment for negative angles.
 *
 * @return RET_SUCCESS on success, or RET_FAIL if an error occurs.
 */
int img_rotate(Image* img, float angle);

#endif // IMG_UTILS_H
