#include <stdio.h>
#if defined(_WIN64) || defined(_WIN32)
// OS Specific functions for windows
#elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
#include <dlfcn.h>
#include <stdlib.h>
typedef void *DLLHandle;

void *load_handle(const char *filename)
{
    void *handle = dlopen(filename, RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    return handle;
}

void *get_function_by_name(DLLHandle handle, const char *name) { return dlsym(handle, name); }
#endif