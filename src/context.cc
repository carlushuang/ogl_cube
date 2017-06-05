
#include "context.hpp"
#include "application.hpp"

Context::Context(const WindowInfo &wi):EventHandler(){
    if (!glfwInit())
        exit(EXIT_FAILURE);
    /* glfw window and context */
    //glfwWindowHint(GLFW_SAMPLES, config.w_aa);

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
    window = glfwCreateWindow(wi.width, wi.height, wi.title.c_str(), NULL, NULL);
    if( window == NULL ){
        std::cout<<"glfwCreateWindow fail"<<std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;
    glewInit();

    set_steady_window(window);
    set_steady_handler(this);
    set_window_handlers();
    std::cout<<"Opengl Version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL Version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;

    /* some global config */
    glEnable(GL_DEPTH_TEST);
#ifdef _MSAA_
    glEnable(GL_MULTISAMPLE);
#endif
    glDepthFunc(GL_LEQUAL);
}
Context::~Context(){
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout<<"Context dtor"<<std::endl;
}
void Context::poll(){
    glfwPollEvents();
}
void Context::wait(){
    glfwWaitEvents();
}
void Context::swap_buffer(){
    glfwSwapBuffers(window);
}
bool Context::should_close(){
    return glfwWindowShouldClose(window)?true:false;
}
