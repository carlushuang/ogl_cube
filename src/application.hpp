#ifndef __APPLICATION_HPP
#define __APPLICATION_HPP

#include "gl_common.hpp"

#include <atomic>
#include <thread>
#include <string>
#include <memory>

#include "context.hpp"
#include "scene.hpp"

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

    Context & get_context(){return *this;}
private:
    Scene scene;
    std::atomic_int frame_cnt;
    std::atomic_bool thread_should_exit;
    std::thread fps_thread;

    void draw_frame();
};

#endif /* __APPLICATION_HPP */