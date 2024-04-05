/**
 * @file internal_img_png.h
 * Provides internal utility functions for reading from and writing to PNG files.
 */

#ifndef INTERNAL_IMG_PNG_H
#define INTERNAL_IMG_PNG_H

#include <png.h>
#include "../../include/img_utils.h" // Include the public API for type definitions

/**
 * Writes an Image to a PNG file.
 * 
 * This function takes a pointer to an Image structure and writes it to the specified PNG file. 
 * It handles the conversion of the internal Image format to the PNG format, ensuring 
 * the image data is correctly saved. The function deals with any necessary color space 
 * conversions and applies the PNG compression algorithm.
 *
 * @param filename The path to the file where the image should be saved. The function 
 *                 will overwrite the file if it already exists.
 * @param img The pointer to the Image structure containing the image data to be saved.
 */
void img_png_write(const char *filename, Image *img);

/**
 * Opens a PNG file and reads it into an Image structure.
 * 
 * This function takes an open file pointer to a PNG file, reads the image data, and 
 * constructs an Image structure from it. It handles the PNG decoding process, including 
 * decompression and color space conversion, to match the internal Image format.
 * 
 * The function is responsible for allocating memory for the new Image structure 
 * and the pixel data. The caller is responsible for freeing this memory using the 
 * appropriate function from the public API when the image is no longer needed.
 *
 * @param fp The file pointer to an open PNG file. The file should be opened in binary 
 *           read mode. The function does not close the file; the caller is responsible 
 *           for closing it.
 * 
 * @return A pointer to the newly created Image structure containing the decoded image 
 *         data. If the function encounters an error during the reading or decoding process, 
 *         it returns NULL.
 */
Image* img_png_open(FILE *fp);

#endif // INTERNAL_IMG_PNG_H