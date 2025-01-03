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


    /* Render loop */
    // Check if window has closed
    while(!mainWindow.isClosed()){
        if(mainWindow.getInput(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mainWindow.close();
            cout << "Closed\n";
        }

        mainWindow.clear(0.2f,0.3f,0.3f);

        // Draw the triangle
        triangle.render();

        mainWindow.render();

    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
