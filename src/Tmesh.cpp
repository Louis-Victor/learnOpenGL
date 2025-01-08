#include "Tmesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glHelper.h"
#include <iostream>
#include <cstring>
#include "Shader.h"

Tmesh::Tmesh(float* m_vertices, unsigned int m_numVert,const Shader& m_shader,unsigned int m_numCol, unsigned int m_numTex):numVert(m_numVert),shader(m_shader),numCol(m_numCol),numTex(m_numTex){
    // copy vertices
    vertices = new float[numVert*(3+numCol+numTex)];
    memcpy(vertices,m_vertices,numVert*(3+numCol+numTex)*sizeof(float));


    // Generates vertex array objects
    glGenVertexArrays(1,&VAO);
    // Generates vertex buffer objects
    glGenBuffers(1,&VBO);

    // Copy vertices to buffer
    // Bind VAO
    glBindVertexArray(VAO);
    // Bind VBO to vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // Copy data into buffer
    glBufferData(GL_ARRAY_BUFFER,numVert*(3+numCol+numTex)*sizeof(float),vertices,GL_STATIC_DRAW);
    // How to read position data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,(3+numCol+numTex)*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    // How to read color data
    glVertexAttribPointer(1,numCol,GL_FLOAT,GL_FALSE,(3+numCol+numTex)*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // How to read texture data
    glVertexAttribPointer(2,numTex,GL_FLOAT,GL_FALSE,(3+numCol+numTex)*sizeof(float),(void*)((3+numCol)*sizeof(float)));
    glEnableVertexAttribArray(2);
    shader.use();
}


void Tmesh::render(){
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,numVert);

}

Tmesh::~Tmesh(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

const Shader& Tmesh::getShaderProgram(){ return shader;}
