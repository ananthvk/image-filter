#include "image_filter.h"
#include <iostream>
extern "C"
{
    const char *Plugin_Name() { return "Some other features"; }

    const char *Plugin_Id() { return "002"; }

    void Plugin_Init()
    {
        // Perform initialization, such as registering commands
    }

    void Plugin_Destroy()
    {
        // Cleanup resources
    }

}
