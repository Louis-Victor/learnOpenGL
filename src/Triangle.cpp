#include "Triangle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glHelper.h"
#include <iostream>

float defaultVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

Triangle::Triangle(float* m_vertices){
    // copy vertices
    for(int i=0;i<9;i++){
        vertices[i] = m_vertices[i];
    }

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
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    // How to read triangle data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    // Enable location 0 in vertex shader
    glEnableVertexAttribArray(0);
}

Triangle::Triangle() : Triangle(defaultVertices){}

void Triangle::render(){
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);
}
