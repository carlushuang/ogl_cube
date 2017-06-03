#ifndef __APPLICATION_HPP
#define __APPLICATION_HPP

#include "gl_common.hpp"

#include <atomic>
#include <thread>
#include <string>
#include <memory>

#include "event_handler.hpp"

//#include "camera.hpp"
//#include "cube.hpp"
//#include "context.hpp"
class Camera;
class Cube;
class Context;

class Application : public EventDispatcher{
public:
    static const std::string WINDOW_TITLE;
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const int FPS;
    Application();
    ~Application();
    void startMainLoop();

    Camera & get_camera() {return *camera;}
    virtual void dispatch_key_pressed(int key);
    virtual void dispatch_scroll(double xoffset, double yoffset);
private:
    // order important! will dtor in reverse order
    std::unique_ptr<Context> context;
    std::unique_ptr<Cube>    cube;
    std::unique_ptr<Camera>  camera;

    std::atomic_int frame_cnt;
    std::atomic_bool thread_should_exit;
    std::thread fps_thread;

    void draw_frame();
};

#endif /* __APPLICATION_HPP */