# OpenGL_Application

##  Description
Very simple entry point for  OpenGl applications.

## How to use

Make sure you have installed GLEW 

### Windows
1. Clone the project 
2. Create a build directory in project folder and run cmake
   ```
   mkdir build
   cd build
   cmake ..
   ```
3. Build the project
   ```
   cmake --build .
   ``` 

## USAGE
All you need to do is navigate to the "src/Tests" folder and create your custom "Test" class, inheriting from the base "Test" class.
Depending on your needs, you can override specific functions. 

For a better understanding, you can refer to the example files "SimpleTriangle.cpp" and "SimpleTriangle.h."
These files provide a clear illustration of the implementation.
