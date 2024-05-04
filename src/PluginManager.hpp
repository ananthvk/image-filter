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

  public:
    Plugin(const std::string &path) : path(path)
    {
        handle = load_handle(path.c_str());
        if (!handle)
        {
            throw std::runtime_error(get_dll_error());
        }
        std::cout << "[INFO] Loaded plugin: " << path << std::endl;
    }

    ~Plugin()
    {
        close_handle(handle);
        std::cout << "[INFO] "
                  << "Unloaded " << path << std::endl;
    }
};

class PluginManager
{
    std::vector<std::shared_ptr<Plugin>> plugins;

  public:
    // Load all plugins from the specified path
    void load_from_directory(const std::filesystem::path &path)
    {
        // First check if the path exists
        if (!std::filesystem::exists(path))
        {
            std::cerr << "[ERROR] Loading plugins: " << path << " does not exist" << std::endl;
            return;
        }
        if (!std::filesystem::is_directory(path))
        {
            std::cerr << "[ERROR] Loading plugins: " << path << " is not directory" << std::endl;
            return;
        }
        for (const auto &dirEntry : std::filesystem::directory_iterator(path))
        {
            // Check if the entry exists, also check if it is a regular file or a symlink
            if (std::filesystem::exists(dirEntry) && (std::filesystem::is_regular_file(dirEntry) ||
                                                      std::filesystem::is_symlink(dirEntry)))
            {
                // Check if the file has the OS specific extension - i.e. .dll for windows, .so for
                // linux
                if (dirEntry.path().extension() != get_plugin_extension())
                {
                    continue;
                }
                try
                {
                    // Load the plugin
                    plugins.push_back(std::make_shared<Plugin>(dirEntry.path().generic_string()));
                }
                catch (std::exception &e)
                {
                    std::cerr << "[ERROR] Could not load " << dirEntry << std::endl;
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    size_t number_of_plugins_loaded() { return plugins.size(); }

    // Unloads all loaded plugins
    void unload() { plugins.clear(); }
};