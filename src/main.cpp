#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cmath>
#include "stb_image.h"

// GLFW & GLEW include
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include </usr/include/GLFW/glfw3.h>
//#include <GLES2/gl2.h>
//#include <EGL/egl.h>
// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glHelper.h"
#include "Window.h"
//#include "Triangle.h"
#include "Mesh.h"
#include "Tmesh.h"
#include "Shader.h"
#include "Texture.h"


using namespace std;
const float screen = 1920.0f/1080.0f;


const unsigned int shaderCount = 2;
const char* shaderList[shaderCount] = {
    "main.vert",
    "main.frag"
};


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
    // 1920x1080
    Window mainWindow(800*screen,800,"mainWindow");
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
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 0
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // 6
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 12
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 18
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 24
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // 30
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f
    };


    Shader shader(shaderList,shaderCount);
    Tmesh mesh(vertices,36,shader,4,2);

    // load texture
    Texture texture1("container.jpg","texture1",false,false,0,GL_CLAMP_TO_EDGE);
    Texture texture2("awesomeface.png","texture2",true,true,1);

    texture1.setShaderId(shader);
    texture2.setShaderId(shader);

    // matrix transformations
    // to world coord
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), 
    //        glm::vec3(1.0,0.0,0.0));

    // view matrix
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // projection matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f),screen, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(shader.get(),"model");
    unsigned int viewLoc = glGetUniformLocation(shader.get(),"view");
    unsigned int projectionLoc = glGetUniformLocation(shader.get(),"projection");


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
        if(mainWindow.getInput(GLFW_KEY_UP) == GLFW_PRESS){
            view = glm::translate(view,glm::vec3(0.0f,0.0f,0.1f));
        }else if(mainWindow.getInput(GLFW_KEY_DOWN) == GLFW_PRESS){
            view = glm::translate(view,glm::vec3(0.0f,0.0f,-0.1f));
        }
        if(mainWindow.getInput(GLFW_KEY_RIGHT) == GLFW_PRESS){
            view = glm::translate(view,glm::vec3(-0.1f,0.0f,0.0f));
        }else if(mainWindow.getInput(GLFW_KEY_LEFT) == GLFW_PRESS){
            view = glm::translate(view,glm::vec3(0.1f,0.0f,0.0f));
        }

        mainWindow.clear(0.2f,0.3f,0.3f);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

        texture1.use();
        texture2.use();
        mesh.render();

        mainWindow.render();

    }

    // Clean glfw resources
    cout << "Closing GLFW\n";
    glfwTerminate();
    cout << "GLFW Closed\n";

    return 0;
}
