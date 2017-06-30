#ifdef TEST_MODEL
#include "model.hpp"
#include <iostream>
#include "gl_common.hpp"

int main(int argc, char ** argv){
    if(argc == 1){
        std::cerr<<"ERROR: image path not provided"<<std::endl;
        return -1;
    }
    if (!glfwInit())
        exit(EXIT_FAILURE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _MSAA_
    // color/depth/stencil affected
    glfwWindowHint(GLFW_SAMPLES, 4);
#endif
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     GLFWwindow* window = glfwCreateWindow(800, 600, "test_model", NULL, NULL);
    if( window == NULL ){
        std::cout<<"glfwCreateWindow fail"<<std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    const char * file_path = argv[1];
    Model model(file_path);
    model.dump_model();
} 
#endif /*TEST_MODEL*/
