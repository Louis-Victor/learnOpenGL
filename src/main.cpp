#include <iostream>
#include <stdio.h>

// GLFW & GLAD include
#include <GLFW/glfw3.h>
//#include </usr/include/GLFW/glfw3.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
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

    /* Vertex Input */
    // A triangle
    float vertices[] =
    {
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.0f, 0.5f,0.0f
    };
    
    // Generates buffer objects
    unsigned int VBO;
    glGenBuffers(1,&VBO);

    // Bind VBO buffer to a vertex buffer (GL_ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    // Copy data into buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    /* Vertex Shader */
    const char *vertexShaderSource = ""
        "#version 330 core\n"
        "layout (location = 0) in vec3 apos;\n"
        "void main(){\n"
        "   gl_Position = vec4(apos.x,apos.y,apos.z,1.0);\n"
        "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    
    // Verify compilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        cout << "error::shader::vertex::compilation_failed\n" << infoLog << "\n";
        return 1;
    }

    /* Fragment Shader */
    const char *fragmentShaderSource = ""
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main(){\n"
        "fragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
        "}\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    // Check for errors
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        cout << "error::shader::fragment::compilation_failed\n" << infoLog << "\n";
        return 1;
    }

    /* Shader Program */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for errors
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        cout << "error::shader::program::linking_failed\n" << infoLog << "\n";
        return 1;
    }

    glUseProgram(shaderProgram);

    // Not needed anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    /* Render loop */
    // Check if window has closed
    while(!mainWindow.isClosed()){
        mainWindow.clear(0.2f,0.3f,0.3f);
        mainWindow.render();

        if(mainWindow.getInput(GLFW_KEY_ESCAPE) == GLFW_PRESS){
            mainWindow.close();
            cout << "Closed\n";
        }
    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
