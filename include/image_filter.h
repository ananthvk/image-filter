#pragma once
#include <stdint.h>

extern "C"
{
    // This function should return the name of the plugin
    const char *Plugin_Name();

    uint8_t *ImageFilter_create_image(int width, int height, int channels);

    bool ImageFilter_write_image(const char *filename, int width, int height, int channels, uint8_t *data);

    void ImageFilter_destroy_image(uint8_t *data);
    
    void ImageFilter_set_image(int width, int height, int channels, uint8_t* data);
    
    int ImageFilter_get_width();

    int ImageFilter_get_height();

    int ImageFilter_get_channels();
    
    uint8_t* ImageFilter_get_image();

    // bool ImageFilter_load_image(const char *filename, int width, int height, int channels, uint8_t *data);
}