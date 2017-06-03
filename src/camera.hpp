#ifndef __CAMERA__HPP
#define __CAMERA__HPP

#include "gl_common.hpp"

#include "event_handler.hpp"

class Camera{
    /* arc ball rotate camera */
public:
    Camera(float _fov);
    ~Camera();

    void handle_control(Control ctrl);
    const glm::mat4 & update_proj_view();

private:
    float fov;
    float radius;

    glm::vec3 cur_position;
    glm::vec3 cur_up;
    float pitch; // head up/down
    float yaw;  // turn left/right
    float roll; // wing level
    void update_position();
    void reset_position();

    // final matrix
    glm::mat4 mat_proj_view;
};

#endif /*__CAMERA__HPP*/
