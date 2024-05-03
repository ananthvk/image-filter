#include "os_specific_impl.hpp"
#pragma once
struct AppContext;

class Plugin
{
    DLLHandle handle;

  public:
    void set_handle(DLLHandle handle) { this->handle = handle; }

    void Init(AppContext *context) {
        void *fptr = get_function_by_name(handle, "Plugin_Init");
    }

    void SetName(AppContext *context, const char *name) {
        void *fptr = get_function_by_name(handle, "Plugin_SetName");
    }

    void Execute(AppContext *context) {
        void *fptr = get_function_by_name(handle, "Plugin_Execute");
    }

    void Destroy(AppContext *context) {
        void *fptr = get_function_by_name(handle, "Plugin_Destroy");
    }
};