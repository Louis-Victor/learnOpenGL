#ifndef __TMESH__
#define __TMESH__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

// Mesh class
class Tmesh{
    private:
        float* vertices;
        unsigned int  numVert;
        unsigned int numCol; // num colors
        unsigned int numTex; // texture coord
        // vertex array object
        unsigned int VAO;
        // vertex buffer object
        unsigned int VBO;

        // Shader program
        Shader shader;

    public:
        Tmesh(float* m_vertices,unsigned int m_numVert,const Shader& m_shader, unsigned int m_numCol, unsigned int m_numTex);
        void render();
        ~Tmesh();
        const Shader& getShaderProgram();
};


#endif
