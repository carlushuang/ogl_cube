#ifndef __APPLICATION_HPP
#define __APPLICATION_HPP

#include "gl_common.hpp"

#include <atomic>
#include <thread>
#include <string>
#include <memory>

#include "event_handler.hpp"
#include "context.hpp"

class Camera;
class Cube;

struct WindowInfo{
    int width;
    int height;
    std::string title;
};

class Application : public Context{
public:
    static const WindowInfo window_info;
    static const int FPS;
    static const int FPS_SAMPLE_MSEC;
    Application();
    ~Application();
    void start_main_loop();

    Camera & get_camera() {return *camera;}
    virtual void dispatch_key_pressed(int key);
    virtual void dispatch_scroll(double xoffset, double yoffset);
    Context & get_context(){return *this;}
private:
    // ctor order important! will dtor in reverse order
    std::unique_ptr<Cube>    cube;
    std::unique_ptr<Camera>  camera;

    std::atomic_int frame_cnt;
    std::atomic_bool thread_should_exit;
    std::thread fps_thread;

    void draw_frame();
};

#endif /* __APPLICATION_HPP */