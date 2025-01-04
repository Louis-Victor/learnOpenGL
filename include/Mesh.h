#ifndef __MESH__
#define __MESH__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

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
        Shader shader;

    public:
        Mesh(float* m_vertices,unsigned int m_numVert,unsigned int* m_indices,unsigned int m_numInd,const Shader& m_shader);
        void render();
        ~Mesh();
        const Shader& getShaderProgram();
};


#endif
