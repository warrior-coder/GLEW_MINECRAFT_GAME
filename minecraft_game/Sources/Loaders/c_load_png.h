#ifndef C_LOAD_PNG_H
#define C_LOAD_PNG_H


#include <stdio.h>
#include <stdlib.h>

#include <GLEW/glew.h>
#include <png.h>


GLuint c_load_png(const char* fileName, GLuint* width_ptr, GLuint* height_ptr);


#endif // !C_LOAD_PNG_H

