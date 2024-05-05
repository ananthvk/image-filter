#pragma once
#include "os_specific_impl.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * This class represents a plugin (shared object).
 * It holds a handle to the shared library, and path to the shared library file
 */
class Plugin
{
    DLLHandle handle;
    std::filesystem::path path;
    const char *(*plugin_get_name)();
    const char *(*plugin_get_id)();

  public:
    Plugin(const std::filesystem::path &path);

    ~Plugin();

    const char *get_name();

    const char *get_id();
};

/*
 * This class manages a number of plugins.
 */
class PluginManager
{
    std::vector<std::shared_ptr<Plugin>> plugins;
    std::set<std::string> plugin_ids;

  public:
    void load_from_directory(const std::filesystem::path &path);

    void init();

    size_t number_of_plugins_loaded();

    void unload();
};