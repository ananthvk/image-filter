#include "image-filter.h"
extern "C"
{
    const char* Plugin_Name()
    {
        Foo();
        return "First plugin";
    }
}
