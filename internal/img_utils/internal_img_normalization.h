#ifndef INTERNAL_IMG_NORMALIZATION_H
#define INTERNAL_IMG_NORMALIZATION_H

#include "../../include/img_utils.h" // Include the public API for type definitions

void img_normalize_pixel_values(Image *img, float new_min, float new_max);


#endif // INTERNAL_IMG_NORMALIZATION_H