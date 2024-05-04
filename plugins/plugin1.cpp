#include "image_filter.h"
extern "C"
{
    const char* Plugin_Name()
    {
        auto img = ImageFilter_create_image(400, 400, 4);
        for(int i = 0; i < 400 * 400 * 4; i++)
            img[i] = 255;
        ImageFilter_write_image("First_plugin.png", 400, 400, img, 4);
        ImageFilter_destroy_image(img);
        return "Example of a plugin";
    }
}
