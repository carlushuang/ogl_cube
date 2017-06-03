#include "application.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "context.hpp"

#include <iostream>
#include <chrono>

const std::string Application::WINDOW_TITLE="ogl_cube";
const int Application::WINDOW_WIDTH=1080;
const int Application::WINDOW_HEIGHT=720;
const int Application::FPS = 60;
Application::Application():
    context(new Context(this)),
    cube(new Cube(this)),
    camera(new Camera((float)Application::WINDOW_WIDTH/(float)Application::WINDOW_HEIGHT)),
    frame_cnt(0),
    thread_should_exit(false)
{

}
void Application::startMainLoop(){
    fps_thread=std::move(std::thread([&,this](){
        const static int SAMPLE_MSEC = 1400;
        std::this_thread::sleep_for(std::chrono::milliseconds(SAMPLE_MSEC));
        while(!thread_should_exit){
            int frames = frame_cnt.exchange(0);
            //std::cout<<"FPS:"<<((float)frames)*1000/SAMPLE_MSEC<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(SAMPLE_MSEC));
        }
    }));

    while(!context->should_close()){
        auto time_start = std::chrono::steady_clock::now();
        auto time_next = time_start +
                std::chrono::microseconds(1000000 / Application::FPS);
        draw_frame();
        context->swap_buffer();
        context->poll();

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
    camera->handle_control(context->get_key_control(key));
}
void Application::dispatch_scroll(double xoffset, double yoffset){
    camera->handle_control(context->get_scroll_control(xoffset, yoffset));
}
