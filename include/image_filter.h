#pragma once
#include <stdint.h>

extern "C"
{
    // This function should return the name of the plugin, this *MUST* be implemented by a plugin.
    const char *Plugin_Name();

    // This function should return a unique identifier of the plugin (preferably an UUID), this
    // *MUST* be implemented by a plugin. It is used to detect duplicate plugins.
    const char *Plugin_Id();
    /*
     * Creates an image, which is of size `width * height * channels` bytes
     * For example, an image with 4 channels (RGBA) would be represented as
     * | C1 | C2 | C3 | C4 | C1 | C2 | C3 | C4 | C1 | C2 |...
     * Where each channel is one byte (0-255) and represents the value of that channel
     * @param width width of the image (in pixels)
     * @param height height of the image (in pixels)
     * @param channels number of channels (3 for RGB, 4 for RGBA)
     * @return Array of unsigned one byte integers
     * @brief Returns a new unitialized image, of size `width * height * channels` bytes
     */
    uint8_t *ImageFilter_create_image(int width, int height, int channels);

    /*
     * @brief Writes the image to disk, currently only png files are supported
     * @param filename - Path of the file to be written
     * @param width - Width of the image
     * @param height - Height of the image
     * @param channels - Number of channels in the image(3 for RGB, 4 for RGBA)
     * @param data - Actual image data as a sequence of bytes (of length `width * height *
     * channels`)
     * @return `true` if the write was successfull, otherwise `false`
     */
    bool ImageFilter_write_image(const char *filename, int width, int height, int channels,
                                 uint8_t *data);

    /*
     * Note: This function must not be called on image which has been set with
     * ImageFilter_set_image. This function should not be called by plugins on the image returned
     * from ImageFilter_get_image
     * @param data  Pointer to sequence of bytes representing the image
     * @brief This function frees memory associated with an image
     */
    void ImageFilter_destroy_image(uint8_t *data);

    /*
     * This function sets an image returned by `ImageFilter_create_image`. After calling this function
     * ownership of data is transferred to the main program. The plugin *MUST* not free or delete data
     * @param width width of the image
     * @param height height of the image
     * @param channels number of channels in the image
     * @param data pointer to sequence of bytes representing the image
     */
    void ImageFilter_set_image(int width, int height, int channels, uint8_t *data);

    // Returns the width of the global stored image
    int ImageFilter_get_width();

    // Returns the height of the global stored image
    int ImageFilter_get_height();

    // Returns the number of channels of the global stored image
    int ImageFilter_get_channels();

    // Returns the global stored image
    uint8_t *ImageFilter_get_image();

    // Loads an image from disk and stores it as the global image
    // @param filename - File to load
    // @return true if the load succeeds, otherwise false
    bool ImageFilter_load_image(const char *filename);

    // This function frees the global stored image
    void ImageFilter_reset();
}