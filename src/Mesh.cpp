#include "Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glHelper.h"
#include <iostream>
#include <cstring>

Mesh::Mesh(float* m_vertices, unsigned int m_numVert,unsigned int* m_indices, unsigned int m_numInd):numVert(m_numVert),numInd(m_numInd){
    // copy vertices
    vertices = new float[numVert];
    memcpy(vertices,m_vertices,numVert*sizeof(float));
    // copy indices
    indices = new unsigned int[numInd];
    memcpy(indices,m_indices,numInd*sizeof(int));

    // Compiles and links shaders
    const unsigned int numShader = 2;
    unsigned int shaders[numShader];
    shaders[0] = compileShaderFromSource("shaders/mainVertexShader.vert");
    shaders[1] = compileShaderFromSource("shaders/mainFragmentShader.frag");
    if(createShaderProgram(shaderProgram,shaders,numShader)) std::cout << "Linking Successful\n";
    else exit(1);
    // delete shaders after compilation
    for(unsigned int i=0;i<numShader;i++){
        glDeleteShader(shaders[i]);
    }

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
    // How to read triangle data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    // Enable location 0 in vertex shader
    glEnableVertexAttribArray(0);
    // Generate EBO buffer object
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,numInd*sizeof(unsigned int),indices,GL_STATIC_DRAW);
}


void Mesh::render(){
    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES,numInd,GL_UNSIGNED_INT,0);
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);
}
