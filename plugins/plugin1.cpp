#include "image_filter.h"
#include <iostream>
extern "C"
{
    const char *Plugin_Name() { return "Example of a plugin"; }

    const char *Plugin_Id() { return "001"; }

    void Plugin_Init()
    {
        // Perform initialization, such as registering commands
    }

    void Plugin_Destroy()
    {
        // Cleanup resources
    }

}
