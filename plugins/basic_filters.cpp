#include "image_filter.h"
#include <iostream>
extern "C"
{
    const char *Plugin_Name() { return "Basic filters"; }

    const char *Plugin_Id() { return "001"; }

    void *blur(void *arg) { std::cout << "Blur filter is being run" << std::endl; return NULL;}

    void Plugin_Init()
    {
        // Perform initialization, such as registering commands
        PluginManager_register("blur", blur);
        PluginManager_register("blur2", blur);
        PluginManager_register("--blur3", blur);
    }

    void Plugin_Destroy()
    {
        // Cleanup resources
    }

}