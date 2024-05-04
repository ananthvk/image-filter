# image-filter

The goal of this project is to implement a cross platform plugin system for an image filter application. The plugins should be compiled as either `.dll` or as `.so` and placed in a folder. The main program should find all plugins, load them and execute them depending upon the requirements.
Plugins are widely used in various applications to provide the user a way to extend functionality without recompiling. Examples include browser plugins, VS Code extensions, game mods, etc.

## What Are Image Filters?

Image filters are algorithms which operate on images (2 dimensional array of pixels) to produce various outputs. For example a blur filter blurs the input image, a sharpen mask sharpens the image, etc.
These filters could be implemented directly in the main application but that would mean for each new filter, the application has to be recompiled. To avoid that, the filters can be implemented as shared objects (`.dll / .so`).

## Requirements

- Dynamic loading of code using shared objects / DLLs
- Command line application

## Possible Usage

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
To run a filter type
image-filter <input_file_name> <filter_name> <filter params> 
```

Example:
```
$ image-filter cat.png blur 3
```

## API

A plugin manager should read all shared objects / DLLs in a directory, use `dlopen` or `LoadLibraryEx` to load it, then find the required symbols.

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

