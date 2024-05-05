# image-filter

The goal of this project is to implement a cross platform plugin system for an image filter application. The plugins should be compiled as either `.dll` or as `.so` and placed in a folder. The main program should find all plugins, load them and execute them depending upon the requirements.
Plugins are widely used in various applications to provide the user a way to extend functionality without recompiling. Examples include browser plugins, VS Code extensions, game mods, etc.

## What Are Image Filters?

Image filters are algorithms which operate on images (2 dimensional array of pixels) to produce various outputs. For example a blur filter blurs the input image, a sharpen mask sharpens the image, etc.
These filters could be implemented directly in the main application but that would mean for each new filter, the application has to be recompiled. To avoid that, the filters can be implemented as shared objects (`.dll / .so`).

## Requirements

- Dynamic loading of code using shared objects / DLLs
- Command line application

## Planned Usage
```
$ ls plugins
blur.so sharpen.so filters_3.so

$ image-filter -h
Loaded three 5 filters
blur.so
	blur - Blur filter
sharpen.so
	sharpen - Sharpen filter
filters_3.so
	A - FilterA
	B - FilterB
	C - FilterC
```
Interactive mode:
```
$ image-filter
> load cat.png 
> blur 50
> grayscale
> save cat_out.png
> exit
```

## API

A plugin manager should read all shared objects / DLLs in a directory, use `dlopen` or `LoadLibraryEx` to load it, then find the required symbols.

The plugin has the following API available to use.
```
uint8_t *ImageFilter_create_image(int width, int height, int channels);
bool ImageFilter_write_image(const char *filename, int width, int height, int channels, uint8_t *data);
void ImageFilter_destroy_image(uint8_t *data);
void ImageFilter_set_image(int width, int height, int channels, uint8_t* data);
int ImageFilter_get_width();
int ImageFilter_get_height();
int ImageFilter_get_channels();
uint8_t* ImageFilter_get_image();
bool ImageFilter_load_image(const char *filename, int width, int height, int channels, uint8_t *data);
```

The Plugin must implement the following API
```
extern "C" 
{
    const char* Plugin_Name()
    {
        
    }
}
```

## How to run?

Currently, for demonstrating runtime loading of plugins, this project builds a subproject `plugins`, after which the shared library files are stored in `plugins` folder of the build directory.

To run this project,
```
$ git clone https://github.com/ananthvk/image-filter
$ cd image-filter
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./image-filter
```

