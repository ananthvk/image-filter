#include "plugin_manager.hpp"

int main()
{
    std::cout << "[INFO] Started application" << std::endl;
    PluginManager manager;
    manager.load_from_directory(get_plugin_dir());
    std::cout <<"[INFO] Loaded " << manager.number_of_plugins_loaded() << " plugins" << std::endl;
}