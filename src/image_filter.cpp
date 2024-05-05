#include "image_filter.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdlib.h>

extern "C"
{
    uint8_t *ImageFilter_create_image(int width, int height, int channels)
    {
        return (uint8_t *)malloc(width * height * channels);
    }

    bool ImageFilter_write_image(const char *filename, int width, int height, int channels, uint8_t *data)
    {
        if (!stbi_write_png(filename, width, height, channels, data, width * channels))
        {
            return false;
        }
        return true;
    }

    void ImageFilter_destroy_image(uint8_t *data) { free(data); }
}