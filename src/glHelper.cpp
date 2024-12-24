#include "glHelper.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

// Window resize function
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    //std::cout << "(" << width << "," << height << ")\n";
    glViewport(0,0,width,height);
}

bool setUpGL(){
    bool succ = glfwInit();

    if(succ){
        // Major and minor opengl versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

        // Sets up opengl profile
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    }

    return succ;
}

