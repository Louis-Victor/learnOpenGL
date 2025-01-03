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
#include "Triangle.h"


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

    // A triangle
    Triangle triangle;

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,  // top left
         0.0f,  0.9f, 0.0f   // middle top
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,   // second triangle
        0, 3, 4    // third triangle
    };

    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    // Element buffer object
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);



    /* Render loop */
    // Check if window has closed
    while(!mainWindow.isClosed()){
        if(mainWindow.getInput(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mainWindow.close();
            cout << "Closed\n";
        }

        mainWindow.clear(0.2f,0.3f,0.3f);

        // Draw the triangle
        //triangle.render();
        
        // wireframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // filled
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Draw rectangle
        glUseProgram(shaderProgram);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
        //glBindVertexArray(0);

        mainWindow.render();

    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
