#ifndef __TRIANGLE__
#define __TRIANGLE__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Triangle class
class Triangle{
    private:
        float vertices[9];
        // vertex array object
        unsigned int VAO;
        // vertex buffer object
        unsigned int VBO;
        // Shader program
        unsigned int shaderProgram;

    public:
        Triangle();
        Triangle(float* m_verticves);
        void render();
};


#endif
