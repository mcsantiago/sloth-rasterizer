# Tiny Sloth Graphics Renderer (a [tiny-rasterizer](https://github.com/ssloy/tinyrenderer) sapling)

This project is a simple 3D model rendering program implemented in C++. It reads a Wavefront OBJ file (.obj) containing a 3D model description and renders it to an output image in TGA format (.tga).

## Features

- Reads a Wavefront OBJ file (.obj) and parses the vertex and face data.
- Renders the 3D model using line drawing algorithms.
- Outputs the rendered image to a TGA file (.tga).
- Supports flipping the image vertically to have the origin at the left bottom corner.
- Provides a command-line interface.

## Prerequisites

To build and run the project, you need to have the following installed:

- C++ compiler (supporting C++11 or higher)
- GNU Make (or any other compatible build system)
- TGA library (provided in this project)

## Getting Started

1. Clone this repository to your local machine or download the source code.
2. Ensure that the required prerequisites are installed.
3. Open a terminal or command prompt and navigate to the project directory.
4. Run the following command to build the project:

   ```bash
   make
   ```

   This command will compile the source files and generate the executable.
5. Run the program by executing the following command:

    ```
    ./bin/main
    ```

    The program will read the specified OBJ file, render the model, and generate the output TGA image file.
6. Once the program finishes, you will find the output image file named output.tga in the project directory.

## Customization

- Input OBJ File: By default, the program is set to read the OBJ file located at "../obj/test_head.obj". If your OBJ file is in a different location or has a different name, you can modify the main function in main.cpp to provide the correct file path.

- Output Image: The program generates the output image file as output.tga. If you want to change the output file name or location, you can modify the image.write_tga_file line in the main function in main.cpp.

## Cleaning Up
To clean up the generated object files and the executable, run the following command:

```bash
make clean
```

This command will remove the object files, the output TGA image file, and the executable.

## License 
This project is licensed under the MIT License.

## Acknowledgments
This project is based on the [tiny-renderer](https://github.com/ssloy/tinyrenderer) project. This project is merely an exercise to 
understand the basics of software rasterization and hopefully act
as the foundation for future GPU-based renderings.