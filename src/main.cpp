#include "plugin_manager.hpp"
void ImageFilter_unload();

int main()
{
    std::cout << "[INFO] Started application" << std::endl;
    PluginManager manager;
    for (const auto &path : get_search_paths())
        manager.load_from_directory(path);
    std::cout << "[INFO] Loaded " << manager.number_of_plugins_loaded() << " plugins" << std::endl;
    manager.init();
    std::string line;
    std::cout << "> ";
    while (std::getline(std::cin, line))
    {
        if (line == "exit" || line == "quit")
            break;
        std::cout << "> ";
    }
    ImageFilter_unload();
}