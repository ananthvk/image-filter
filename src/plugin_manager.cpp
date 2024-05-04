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
        throw std::runtime_error(get_dll_error());
    }
    plugin_get_name = (const char *(*)())fptr;
    std::cout << "[INFO] Loaded plugin: " << path.filename() << std::endl;
}

Plugin::~Plugin()
{
    close_handle(handle);
    std::cout << "[INFO] "
              << "Unloaded " << path.filename() << std::endl;
}

const char *Plugin::get_name() { return plugin_get_name(); }

void PluginManager::load_from_directory(const std::filesystem::path &path)
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
