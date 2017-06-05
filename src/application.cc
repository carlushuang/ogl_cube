#include "application.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "context.hpp"

#include <iostream>
#include <chrono>

const int Application::FPS = 60;
const int Application::FPS_SAMPLE_MSEC = 1400;
const WindowInfo Application::window_info = {.width = 1080, .height = 720, .title="ogl_cube"};
Application::Application():
    Context(window_info),
    cube(new Cube(this)),
    camera(new Camera((float)window_info.width/(float)window_info.height)),
    frame_cnt(0),
    thread_should_exit(false)
{

}
void Application::start_main_loop(){
    fps_thread=std::move(std::thread([&,this](){
        
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS_SAMPLE_MSEC));
        while(!thread_should_exit){
            int frames = frame_cnt.exchange(0);
            //std::cout<<"FPS:"<<((float)frames)*1000/FPS_SAMPLE_MSEC<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(FPS_SAMPLE_MSEC));
        }
    }));

    while(!get_context().should_close()){
        auto time_start = std::chrono::steady_clock::now();
        auto time_next = time_start +
                std::chrono::microseconds(1000000 / Application::FPS);
        draw_frame();
        get_context().swap_buffer();
        get_context().poll();

        frame_cnt++;  // safe for atomic
        // we fix FPS in main thread
        std::this_thread::sleep_until(time_next);
        //std::cout<<"frame~~"<<std::endl;
    }
}
Application::~Application(){
    std::cout<<"closing window"<<std::endl;
    thread_should_exit = true;
    fps_thread.join();
}

void Application::draw_frame(){
    //glClearColor(1.0,1.0,1.0,1.0);
    //glClearColor(.05,.05,.05,1.0);
    glClearColor(.9,.9,.9,.9);
    //glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    cube->draw();
}

void Application::dispatch_key_pressed(int key){
    camera->handle_control(get_context().get_key_control(key));
}
void Application::dispatch_scroll(double xoffset, double yoffset){
    camera->handle_control(get_context().get_scroll_control(xoffset, yoffset));
}
