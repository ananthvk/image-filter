#include "image_filter.h"
#include <iostream>
extern "C"
{
    const char *Plugin_Name() { return "Filters plugin"; }

    const char *Plugin_Id() { return "003"; }

    void Plugin_Init()
    {
        // Perform initialization, such as registering commands
    }

    void Plugin_Destroy()
    {
        // Cleanup resources
    }

}
