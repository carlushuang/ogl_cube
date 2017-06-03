#ifndef __CUBE_HPP
#define __CUBE_HPP

#include "gl_common.hpp"
class Application;


class Cube{
public:
    Cube(Application * _app);
    ~Cube();
    void draw();
private:
    Application * app;
    GLuint vao;
    GLuint vbo;
    GLuint texture;
    GLuint program;

    glm::mat4 mat_model;
};
//--------------------------------------------------------------------------------------

#endif /* __CUBE_HPP */