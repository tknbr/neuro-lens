
#include <png.h>

typedef struct {
	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_bytep *row_pointers;
} Image;


// Function to load a PNG image
Image* load_png_image(const char *filename);

// Function to save a PNG image
int save_png_image(const char *filename, Image *image);

// Function to free the memory allocated for an Image
void free_image(Image *image);