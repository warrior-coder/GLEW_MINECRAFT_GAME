#ifndef _C_LOAD_PNG_H_
#define _C_LOAD_PNG_H_

#include <stdio.h>
#include <malloc.h>

#include <GLEW/glew.h>
#include <png.h>


GLuint c_load_png(const char* fileName, GLuint* width_ptr, GLuint* height_ptr);

#endif // !_C_LOAD_PNG_H_
