#include <iostream>
#include <string>

// Project dependencies
#define GLFW_INCLUDE_NONE       //Else GLFW could override the gl verison by the system one
#include <GLFW/glfw3.h>
#include "../dependencies/include/glad/gl.h"


// Code dependencies
#include "../include/logs.hpp"


// Global flags
#define DEBUG_LOG true


void error_callback(int error, const char* description)
{
    print_to_log(description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}



int main(int argc, char** argv){

    
    // Initialise GLFW and check if successful
    if(!glfwInit()){
        if(DEBUG_LOG){
            print_to_log("Error initializing GLFW.");
        }
        glfwTerminate();
        return -1;
    } else if(DEBUG_LOG) {print_to_log("GLFW intialized.");}

    // Defines the function managing the error callbacks
    glfwSetErrorCallback(error_callback);


    // Creating the window
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        if(DEBUG_LOG){
            print_to_log("Error initializing the window.");
        }
        glfwTerminate();
        return -2;
    } else if(DEBUG_LOG) {print_to_log("Window intialized.");}

    glfwMakeContextCurrent(window);
    int version_glad = gladLoadGL(glfwGetProcAddress);
    if (version_glad == 0){
        if(DEBUG_LOG){
            print_to_log("Error: failed to initialize OpenGL context.");
        }
        glfwTerminate();
        return -2;
    }
    glfwSwapInterval(1);

    double time = glfwGetTime();    // Initialize timer

    while (!glfwWindowShouldClose(window))
    {
        
    }










    // End of program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}