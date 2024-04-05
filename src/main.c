    
/**
neuro-lens/
├── src/
│   ├── image_utils/               # Image manipulation utilities
│   │   ├── image_io.c             # Image loading and saving
│   │   ├── transform.c            # Resizing, cropping, and other transformations
│   │   ├── color_space.c          # Color space conversions
│   │   └── normalization.c        # Normalization and standardization functions
│   │
│   ├── model_utils/               # Utilities for handling ML models
│   │   ├── model_load.c           # Loading models
│   │   ├── inference.c            # Performing inference
│   │   └── postprocess.c          # Processing inference results
│   │
│   ├── data_augmentation/         # Data augmentation (optional)
│   │   └── augmentation.c         # Basic augmentation techniques
│   │
│   └── main.c                     # Main library interface and examples
│
├── include/                       # Public header files for the library modules
│   ├── image_utils.h              # Public API for image manipulation
│   ├── model_utils.h              # Public API for model utilities
│   └── data_augmentation.h        # Public API for data augmentation
│
├── internal/                      # Internal header files not exposed as public API
│   ├── image_utils/               # Internal utilities for image manipulation
│   │   ├── internal_image_io.h    # Internal functions for image I/O
│   │   ├── internal_transform.h   # Internal functions for transformations
│   │   ├── internal_color_space.h # Internal color space conversion functions
│   │   └── internal_normalization.h # Internal normalization functions
│   │
│   ├── model_utils/               # Internal utilities for ML models
│   │   └── internal_model_utils.h # Internal functions for model handling
│   │
│   └── common.h                   # Common definitions for internal use
│
├── bin/                           # Compiled binaries and executables
└── Makefile                       # Build instructions
*/

#include <stdio.h>
#include "../include/img_utils.h"

#define IMG_PATH "/home/tknbr/Documents/projectes/neuro-lens/data/image.png"
#define IMG_COPY_PATH "/home/tknbr/Documents/projectes/neuro-lens/data/resized.png"


int main()
{
    printf("Hello, ML World!\n");

    Image *image = img_load(IMG_PATH);
    if (image == NULL) {
        fprintf(stderr, "Error loading image.\n");
        return -1; // or handle error appropriately
    }

    // Perform operations on the image
    printf("Performing img comptuations\n");
    if (0 != img_resize(&image, (image->width)/2, (image->height)/2 ))
    {
        printf("Image resizing failed.\n");
        img_free(image); // Ensure resources are freed on failure
        return 1;
    }

    if (0 != img_crop(&image, -1+(image->width)/2, -1+(image->height)/2, (image->width)/2, (image->height)/2 ))
    {
        printf("Image crop failed.\n");
        img_free(image); // Ensure resources are freed on failure
        return 1;
    }
    img_rotate(image, 45);
    img_flip_horizontal(image);

    img_write(IMG_COPY_PATH, image);


    // When done, free the image to prevent memory leaks
    img_free(image);
    printf("finishing\n");

    return 0;
}
