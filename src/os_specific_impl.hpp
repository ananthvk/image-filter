#pragma once
#if defined(_WIN64) || defined(_WIN32)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#include <dlfcn.h>
#include <filesystem>
#include <stdlib.h>
#include <string>
#include <vector>
typedef void *DLLHandle;

// Loads a shared object using dlopen() and returns the opened handle
inline void *load_handle(const char *filename) { return dlopen(filename, RTLD_LAZY | RTLD_GLOBAL); }

// Returns a dlerror() as std::string
inline std::string get_dll_error() { return std::string(dlerror()); }

// Get a symbol in a shared library
inline void *get_function_by_name(DLLHandle handle, const char *name)
{
    return dlsym(handle, name);
}

// Close the shared object handle
inline void close_handle(DLLHandle handle) { dlclose(handle); }

// Return path to the directory in which the executable program is present
inline std::filesystem::path get_executable_dir()
{
    // For linux use /proc/self/exe
    return std::filesystem::canonical("/proc/self/exe").parent_path();
}

// Return the shared object extension for this system (.so)
inline const char *get_plugin_extension() { return ".so"; }

// Return paths to check for plugins
inline std::vector<std::filesystem::path> get_search_paths()
{
    std::vector<std::filesystem::path> paths = {
        get_executable_dir(), get_executable_dir().append("plugins"), "~/.image-filter/plugins"};
    return paths;
}
#endif

// A wrapper around get_function_by_name, which throws a runtime error if the symbol is not found
inline void *get_symbol(DLLHandle handle, const char *name)
{
    void *fptr = get_function_by_name(handle, name);
    if (!fptr)
    {
        auto err = get_dll_error();
        close_handle(handle);
        throw std::runtime_error(err);
    }
    return fptr;
}