#include "PluginManager.hpp"

int main()
{
    std::cout << "[INFO] Started application" << std::endl;
    try
    {
        Plugin plugin("/home/shank/code/image-filter/src/example.so");
    }
    catch (std::exception &e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}