#include "plugin_manager.hpp"

Plugin::Plugin(const std::filesystem::path &path) : path(path)
{
    handle = load_handle(path.c_str());
    if (!handle)
    {
        throw std::runtime_error(get_dll_error());
    }
    // Load all required symbols from the DLL
    void *fptr = get_function_by_name(handle, "Plugin_Name");
    if (!fptr)
    {
        auto err = get_dll_error();
        dlclose(handle);
        // If any of them is not found, throw an error
        throw std::runtime_error(err);
    }
    plugin_get_name = (const char *(*)())fptr;
    fptr = get_function_by_name(handle, "Plugin_Id");
    if (!fptr)
    {
        auto err = get_dll_error();
        dlclose(handle);
        // If any of them is not found, throw an error
        throw std::runtime_error(err);
    }
    plugin_get_id = (const char *(*)())fptr;
    std::cout << "[INFO] Loaded plugin: " << path.filename() << std::endl;
}

// Handle is automatically closed when destructor is run
Plugin::~Plugin() { close_handle(handle);}

// Return the name of the plugin
const char *Plugin::get_name() { return plugin_get_name(); }

const char *Plugin::get_id() { return plugin_get_id(); }

// This function loads all shared objects from the given path
void PluginManager::load_from_directory(const std::filesystem::path &path)
{
    // First check if the path exists
    if (!std::filesystem::exists(path))
    {
        return;
    }
    if (!std::filesystem::is_directory(path))
    {
        return;
    }
    for (const auto &dirEntry : std::filesystem::directory_iterator(path))
    {
        // Check if the entry exists, also check if it is a regular file or a symlink
        if (std::filesystem::exists(dirEntry) &&
            (std::filesystem::is_regular_file(dirEntry) || std::filesystem::is_symlink(dirEntry)))
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
                auto plugin = std::make_shared<Plugin>(dirEntry.path().generic_string());
                // Check if the plugin is already loaded, i.e. this is a duplicate
                // If so, remove it
                if (plugin_ids.find(plugin->get_id()) != plugin_ids.end())
                {
                    std::cout << "[INFO] Duplicate plugin " << dirEntry.path().filename()
                              << " found. Removing it" << std::endl;
                    continue;
                }
                plugin_ids.insert(plugin->get_id());
                plugins.push_back(plugin);
            }
            catch (std::exception &e)
            {
                std::cerr << "[ERROR] Could not load " << dirEntry << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void PluginManager::init()
{
    for (auto &plugin : plugins)
    {
        std::cout << "[INFO] Initializing " << plugin->get_name() << std::endl;
    }
}

size_t PluginManager::number_of_plugins_loaded() { return plugins.size(); }

// Unloads all loaded plugins
void PluginManager::unload() { plugins.clear(); }
