#include "Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glHelper.h"
#include <iostream>
#include <cstring>
#include "Shader.h"

Mesh::Mesh(float* m_vertices, unsigned int m_numVert,unsigned int* m_indices, unsigned int m_numInd,const Shader& m_shader):numVert(m_numVert),numInd(m_numInd),shader(m_shader){
    // copy vertices
    vertices = new float[numVert];
    memcpy(vertices,m_vertices,numVert*sizeof(float));
    // copy indices
    indices = new unsigned int[numInd];
    memcpy(indices,m_indices,numInd*sizeof(int));


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
    glBufferData(GL_ARRAY_BUFFER,numVert*sizeof(float),vertices,GL_STATIC_DRAW);
    // How to read position data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,9*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    // How to read color data
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,9*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // How to read texture data
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,9*sizeof(float),(void*)(7*sizeof(float)));
    glEnableVertexAttribArray(2);
    // Generate EBO buffer object
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,numInd*sizeof(unsigned int),indices,GL_STATIC_DRAW);
    shader.use();
}


void Mesh::render(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,numInd,GL_UNSIGNED_INT,0);

}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
}

const Shader& Mesh::getShaderProgram(){ return shader;}
