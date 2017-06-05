#ifndef __EVENT_HANDLER_HPP
#define __EVENT_HANDLER_HPP

#include <iostream>
#include <unordered_map>
#include "gl_common.hpp"

enum class Control{
    CTRL_NONTHING,
    CTRL_CAMERA_LEFT,
    CTRL_CAMERA_RIGHT,
    CTRL_CAMERA_UP,
    CTRL_CAMERA_DOWN,
    CTRL_CAMERA_RESET,
    CTRL_CAMERA_ZOOM_IN,
    CTRL_CAMERA_ZOOM_OUT,
};

class EventDispatcher{
public:
    virtual void dispatch_key_pressed(int key)=0;
    virtual void dispatch_scroll(double xoffset, double yoffset)=0;
};

template<class T>
class EventHandler : public EventDispatcher{
public:
    /* template class to let static member has only one instance per derived class */
    EventHandler(){
        glfwSetErrorCallback(error_callback);   //valid before glfwinit()
    }
    ~EventHandler(){}

    typedef EventHandler<T> Type;  // self type
    typedef int glfw_key_type;      //GLFW_KEY_*
    typedef std::unordered_map<glfw_key_type, Control> key_map_type;

    static Control get_key_control(glfw_key_type key);
    static Control get_scroll_control(double x, double y);
protected:
    static Type* steady_handler;
    static GLFWwindow* steady_window;
    static void set_steady_handler(Type* _steady_handler){steady_handler=_steady_handler;}
    static void set_steady_window(GLFWwindow* _steady_window){steady_window=_steady_window;}
    static void set_window_handlers(){
        glfwSetFramebufferSizeCallback(steady_window, framebuffer_size_callback);
        glfwSetKeyCallback(steady_window, key_callback);
        glfwSetScrollCallback(steady_window, scroll_callback);
    }
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void error_callback(int error, const char* description);
    static key_map_type key_map;
};
template<class T> typename EventHandler<T>::Type* EventHandler<T>::steady_handler=nullptr;
template<class T> GLFWwindow* EventHandler<T>::steady_window=nullptr;
template<class T> typename EventHandler<T>::key_map_type EventHandler<T>::key_map={
    {GLFW_KEY_W, Control::CTRL_CAMERA_UP},
    {GLFW_KEY_S, Control::CTRL_CAMERA_DOWN},
    {GLFW_KEY_A, Control::CTRL_CAMERA_LEFT},
    {GLFW_KEY_D, Control::CTRL_CAMERA_RIGHT},
    {GLFW_KEY_R, Control::CTRL_CAMERA_RESET},
};
template<class T> Control EventHandler<T>::get_key_control(typename EventHandler<T>::glfw_key_type key){
    auto ctrl = key_map.find(key);
    if(ctrl == key_map.end())
        return Control::CTRL_NONTHING;
    return ctrl->second;
}
template<class T> Control EventHandler<T>::get_scroll_control(double x, double y){
    Control ctrl = Control::CTRL_NONTHING;
    if(x == 0.0){
        if(y>0)
            ctrl = Control::CTRL_CAMERA_ZOOM_IN;
        else if(y<0)
            ctrl = Control::CTRL_CAMERA_ZOOM_OUT;
    }
    return ctrl;
}
template<class T> void EventHandler<T>::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
template<class T> void EventHandler<T>::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        //std::cout<<"KEY: "<<key<<std::endl;
        steady_handler->dispatch_key_pressed(key);
    }
}
template<class T> void EventHandler<T>::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //std::cout<<"xoff:"<<xoffset<<" yoff:"<<yoffset<<std::endl;
    steady_handler->dispatch_scroll(xoffset, yoffset);
}
template<class T> void EventHandler<T>::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

#endif /* __EVENT_HANDLER_HPP */