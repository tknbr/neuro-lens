
#include <png.h>

#ifndef INTERNAL_IMG_UTILS_H
#define INTERNAL_IMG_UTILS_H

/**
 * Width, height and 3 chanels for each pixel (RGB)
 */

typedef struct {
	unsigned char R; // 8 bit red
	unsigned char G; // 8 bit green
	unsigned char B; // 8 bit blue
	unsigned char A; // 8 bit alpha
} pixel;



typedef struct {
	int width, height;
	pixel *pixels;
} Image;


Image* img_new(int width, int height);
void img_free(Image* img);
int img_resize(Image** src, int new_width, int new_height);
int img_crop(Image **src, int x, int y, int width, int height);

Image* img_load(const char *filename);
void img_write(const char *filename, Image *img);


/**
 * 
 * He de fer una classe img general i quan faig un load d'un format
 * (com png) s'ha de retornar directament amb el tipus general.
 * 
 * Fer una classe tiny img? on el height i width siguin més petits?
 * 
 */

#endif // INTERNAL_IMG_UTILS_H