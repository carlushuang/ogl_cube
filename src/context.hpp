#ifndef __CONTEXT_HPP
#define __CONTEXT_HPP

#include "gl_common.hpp"
#include "event_handler.hpp"
#include <string>

class WindowInfo;

//--------------------------------------------------------------------------------------
class Context:public EventHandler<Context>{
public:
    Context(const WindowInfo &wi);
    ~Context();

    void poll();    // return immediately
    void wait();    // wait until event happen
    void swap_buffer();
    bool should_close();

private:
    GLFWwindow* window;
};

#endif  /* __CONTEXT_HPP*/