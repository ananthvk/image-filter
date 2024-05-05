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
    std::cout << "Type \"list\" to view the list of available commands and type \"exit\" to exit"
              << std::endl;
    std::cout << "> ";
    while (std::getline(std::cin, line))
    {
        if (line == "exit" || line == "quit")
            break;
        if (line == "list")
            manager.list_commands();
        else
            manager.execute_command(line);
        std::cout << "> ";
    }
    ImageFilter_unload();
}