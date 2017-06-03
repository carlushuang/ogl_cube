#ifndef __CONTEXT_HPP
#define __CONTEXT_HPP

#include "gl_common.hpp"
#include "event_handler.hpp"
class Application;

//--------------------------------------------------------------------------------------
class Context:public EventHandler<Context>{
public:
    Context(Application * _app);
    ~Context();
    void poll();    // return immediately
    void wait();    // wait until event happen
    void swap_buffer();
    bool should_close();
    virtual void dispatch_key_pressed(int key);
    virtual void dispatch_scroll(double xoffset, double yoffset);
private:
    GLFWwindow* window;
    Application* app;
};

#endif  /* __CONTEXT_HPP*/