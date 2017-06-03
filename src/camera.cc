#include "camera.hpp"
#include <iostream>

Camera::Camera(float _fov) :
fov(_fov)
{
    reset_position();
    update_position();
    update_proj_view();
}
Camera::~Camera(){
    std::cout<<"Camera dtor"<<std::endl;
}

void Camera::reset_position(){
    yaw = pitch = roll = 0;
    radius = 5.0f;
}

void Camera::update_position(){
    glm::mat4 pitch_rotate;
    glm::mat4 yaw_rotate;

    pitch_rotate = glm::rotate(pitch_rotate, glm::radians(pitch), {0,1,0}/*world cord*/);
    yaw_rotate = glm::rotate(yaw_rotate, glm::radians(yaw), {1,0,0}/*world cord*/);

    glm::vec3 init_position(glm::vec3(.0f,.0f,radius));
    glm::vec3 init_up(glm::vec3(0,1,0));
    // arc ball rotation,  must yaw->pitch->roll rotation
    cur_position =  glm::vec3( pitch_rotate * yaw_rotate* glm::vec4(init_position, 0) );
    cur_up =  glm::vec3(pitch_rotate * yaw_rotate * glm::vec4(init_up,0) );
}

void Camera::handle_control(Control ctrl){
    static const float rotate_v=1.0f;
    static const float rotate_h=1.0f;
    static const float zoom=1.0f;
    switch (ctrl){
        case Control::CTRL_CAMERA_UP:
            yaw -= rotate_v;
            if(yaw<=-45.0f)
                yaw = -45.0f;
        break;
        case Control::CTRL_CAMERA_DOWN:
            yaw += rotate_v;
            if(yaw>=45.0f)
                yaw = 45.0f;
        break;
        case Control::CTRL_CAMERA_LEFT:
            pitch -= rotate_h;
            if(pitch <= -0.0f)
                pitch = 360.0f;
        break;
        case Control::CTRL_CAMERA_RIGHT:
            pitch += rotate_h;
            if(pitch >= 360.0f)
                pitch = 0.0f;
        break;
        case Control::CTRL_CAMERA_RESET:
            reset_position();
        break;
        case Control::CTRL_CAMERA_ZOOM_IN:
            radius -= zoom;
            if(radius <= 5.0f)
                radius = 5.0f;
        break;
        case Control::CTRL_CAMERA_ZOOM_OUT:
            radius += zoom;
            if(radius >= 50.0f)
                radius = 50.0f;
        break;
        default:
        break;
    }

    //std::cout<<"yaw: "<<yaw<<" pitch:"<<pitch<<std::endl;
    update_position();
    update_proj_view();
    //std::cout<<"  new camera, x:"<<cur_position.x<<" y:"<<cur_position.y<<" z:"<<cur_position.z<<std::endl;
}
const glm::mat4 & Camera::update_proj_view(){
    glm::mat4 mat_view = glm::lookAt(cur_position/*camera*/, glm::vec3(0,0,0)/*lookat*/, cur_up/*up*/);
    glm::mat4 mat_proj = glm::perspective(45.0f, fov, .1f, 100.0f);
    mat_proj_view = mat_proj * mat_view;
    return mat_proj_view;
}
