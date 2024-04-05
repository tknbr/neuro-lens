/**
 * @file internal_img_io.h
 * Provides internal functions for loading and writing images across various formats.
 *
 * This module acts as a central hub for image I/O operations, automatically 
 * determining the appropriate format handler (e.g., PNG, JPEG) based on the file 
 * extension or contents. It abstracts away the specifics of different image formats, 
 * offering a unified interface for image loading and saving within the library.
 */

#ifndef INTERNAL_IMG_IO_H
#define INTERNAL_IMG_IO_H

#include "../../include/img_utils.h" // Include the public API for type definitions
#include "internal_img_png.h" // For handling PNG-specific I/O operations

/**
 * Loads an image from a file.
 * 
 * This function determines the image format based on the file extension and 
 * delegates the loading process to the corresponding format-specific function. 
 * It supports various formats, including but not limited to PNG and JPEG. 
 * The function allocates memory for a new Image structure and populates it 
 * with the image data read from the file.
 *
 * @param filename The path to the image file to be loaded. The file extension 
 *                 is used to infer the image format.
 * 
 * @return A pointer to a newly allocated Image structure containing the loaded 
 *         image data. If the file cannot be opened, the format is not supported, 
 *         or an error occurs during loading, the function returns NULL.
 */
Image* img_io_load(const char *filename);

/**
 * Writes an image to a file.
 * 
 * This function determines the appropriate image format to use for saving based 
 * on the file extension specified in the filename. It delegates the writing 
 * process to the corresponding format-specific function. The function aims to 
 * preserve the original image quality and characteristics as much as possible.
 *
 * @param filename The path to the file where the image will be saved. The file 
 *                 extension is used to infer the desired image format for saving.
 * @param img The pointer to the Image structure containing the image data to 
 *            be saved.
 */
void img_io_write(const char *filename, Image *img);

#endif // INTERNAL_IMG_IO_H
