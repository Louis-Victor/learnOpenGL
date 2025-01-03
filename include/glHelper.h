#ifndef __GLHELPER__
#define __GLHELPER__
#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

// Window resize function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// GLFW set up function
bool setUpGL();

const char* importShader(const char* filename);

unsigned int compileShader(const char* sourceCode, GLenum shaderType);

unsigned int compileShaderFromSource(const char* filename);

#endif
