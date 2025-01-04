#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cmath>

// GLFW & GLEW include
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include </usr/include/GLFW/glfw3.h>
//#include <GLES2/gl2.h>
//#include <EGL/egl.h>
#include "glHelper.h"
#include "Window.h"
//#include "Triangle.h"
#include "Mesh.h"
#include "Shader.h"


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

    float vertices[] = {
        //  x      y     z |   r     g     b     a
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2
    };

    const unsigned int shaderCount = 2;
    const char* shaderList[shaderCount] = {
        "shaders/main.vert",
        "shaders/main.frag"
    };

    Shader shader(shaderList,shaderCount);
    Mesh mesh(vertices,3*7,indices,1*3,shader);


    // texture
    float textureCoord[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    /* Render loop */
    // Check if window has closed
    bool isFill = true;
    bool spaceFlag = false;
    while(!mainWindow.isClosed()){
        if(mainWindow.getInput(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mainWindow.close();
            cout << "Closed\n";
        }
        if(mainWindow.getInput(GLFW_KEY_SPACE) == GLFW_RELEASE && spaceFlag){
            spaceFlag = false;
            if(isFill) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            isFill = !isFill;
        }
        else if(mainWindow.getInput(GLFW_KEY_SPACE) == GLFW_PRESS) spaceFlag = true;

        mainWindow.clear(0.2f,0.3f,0.3f);

        mesh.render();

        mainWindow.render();

    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
