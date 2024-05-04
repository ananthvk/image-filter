#pragma once
#include <stdint.h>

extern "C"
{
    // This function should return the name of the plugin
    const char *Plugin_Name();

    uint8_t *ImageFilter_create_image(int width, int height, int channels);

    bool ImageFilter_write_image(const char *filename, int width, int height, uint8_t *data, int channels);

    void ImageFilter_destroy_image(uint8_t *data);
}