#pragma once
#if defined(_WIN64) || defined(_WIN32)
// OS Specific functions for windows
#elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
#include <dlfcn.h>
#include <filesystem>
#include <stdlib.h>
#include <string>
typedef void *DLLHandle;

inline void *load_handle(const char *filename) { return dlopen(filename, RTLD_LAZY | RTLD_GLOBAL); }

inline std::string get_dll_error() { return std::string(dlerror()); }

inline void *get_function_by_name(DLLHandle handle, const char *name) { return dlsym(handle, name); }

inline void close_handle(DLLHandle handle) { dlclose(handle); }

inline std::filesystem::path get_plugin_dir()
{
    // For linux use /proc/self/exe
    return std::filesystem::canonical("/proc/self/exe").parent_path().append("plugins");
}
inline const char *get_plugin_extension()
{
    return ".so";
}
#endif