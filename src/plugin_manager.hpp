#pragma once
#include "os_specific_impl.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Plugin
{
    DLLHandle handle;
    std::string path;
    const char *(*plugin_get_name)();

  public:
    Plugin(const std::string &path);

    ~Plugin();

    const char *get_name(); 
};

class PluginManager
{
    std::vector<std::shared_ptr<Plugin>> plugins;

  public:
    void load_from_directory(const std::filesystem::path &path);

    void init();

    size_t number_of_plugins_loaded();

    void unload();
};