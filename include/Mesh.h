#ifndef __MESH__
#define __MESH__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Mesh class
class Mesh{
    private:
        float* vertices;
        unsigned int  numVert;
        unsigned int* indices;
        unsigned int  numInd;
        // vertex array object
        unsigned int VAO;
        // vertex buffer object
        unsigned int VBO;
        // Element buffer  object
        unsigned int EBO;
        // Shader program
        unsigned int shaderProgram;

    public:
        Mesh(float* m_vertices,unsigned int m_numVert,unsigned int* m_indices,unsigned int m_numInd);
        void render();
        ~Mesh();
};


#endif
