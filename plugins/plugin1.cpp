#include "image_filter.h"
#include <iostream>
extern "C"
{
    const char *Plugin_Name()
    {
        if (!ImageFilter_load_image("test.png"))
        {
            std::cerr << "Could not file test.png" << std::endl;
            return "ERR";
        }
        int channels = ImageFilter_get_channels();
        int width = ImageFilter_get_height();
        int height = ImageFilter_get_width();
        uint8_t *data = ImageFilter_get_image();
        std::cout << "Width: " << width << " Height: " << height << " Channels:" << channels
                  << std::endl;
        for (int i = 0; i < width * height; i++)
        {
            int avg = (data[i * channels] + data[i * channels + 1] + data[i * channels + 2]) / 3;
            data[i * channels] = avg;
            data[i * channels + 1] = avg;
            data[i * channels + 2] = avg;
        }
        ImageFilter_write_image("test_output.png", width, height, channels, data);
        return "Example of a plugin";
    }

    const char *Plugin_Id() { return "001"; }
}
