#pragma once
#include "os_specific_impl.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

class Plugin
{
    DLLHandle handle;
    std::string path;

  public:
    Plugin(const std::string &path): path(path)
    {
        handle = load_handle(path.c_str());
        if (!handle)
        {
            throw std::runtime_error(get_dll_error());
        }
    }
    ~Plugin()
    {
        close_handle(handle);
        std::cout << "[INFO] " << "Unloaded " << path << std::endl;
    }
};