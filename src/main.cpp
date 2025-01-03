#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

// GLFW & GLEW include
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include </usr/include/GLFW/glfw3.h>
//#include <GLES2/gl2.h>
//#include <EGL/egl.h>
#include "glHelper.h"
#include "Window.h"


using namespace std;


int main(int argc, char** argv){

    glfwTerminate();

    // Starts glfw
    if(setUpGL()){
        cout << "INIT SUCCESSFUL\n"; 
    }else{
        cout << "FAILED INIT\n"; 
        return 1;
    }

    // Create Window object
    Window mainWindow(800,600,"mainWindow");
    if(mainWindow.getWindow() == NULL){
        glfwTerminate();
        return 1;
    }

    // Initiate GLEW
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n";
        return 1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // array shader
    const unsigned int numShader = 2;
    unsigned int shaders[numShader];

    // Vertex Shader 
    shaders[0] = compileShaderFromSource("shaders/mainVertexShader.vert");
    // Fragment Shader
    shaders[1] = compileShaderFromSource("shaders/mainFragmentShader.frag");

    //  Shader Program
    unsigned int shaderProgram;
    if(createShaderProgram(shaderProgram,shaders,numShader)) cout << "Linking Successful\n";
    else return 1;

    // Shader objects not needed anymore
    for(unsigned int i=0; i<numShader;i++){
        glDeleteShader(shaders[i]);
    }

    /* Vertex Input */
    // A triangle
    float vertices[] =
    {
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.0f, 0.5f,0.0f
    };
    
    // Generates vertex array objects
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);

    // Generates vertex buffer objects
    unsigned int VBO;
    glGenBuffers(1,&VBO);

    /* drawing the triangle */
    // 0. copy vertices to buffer
    // Bind VAO
    glBindVertexArray(VAO);
    // Bind VBO buffer to a vertex buffer (GL_ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // Copy data into buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // 1. set vertex attribute pointer
    // how to read triangle data
    // In vertex shader source, layout. Param 1 refers to location = 0
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // Draw call in render loop
    // glUseProgram(shaderProgram);
    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES,0,3);


    /* Render loop */
    // Check if window has closed
    while(!mainWindow.isClosed()){
        if(mainWindow.getInput(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mainWindow.close();
            cout << "Closed\n";
        }

        mainWindow.clear(0.2f,0.3f,0.3f);

        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        mainWindow.render();

    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
