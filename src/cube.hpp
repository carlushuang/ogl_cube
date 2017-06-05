#ifndef __CUBE_HPP
#define __CUBE_HPP

#include "gl_common.hpp"
#include "camera.hpp"
#include "render_object.hpp"

class Cube : public RenderObject{
public:
    Cube();
    ~Cube();
    
    virtual void update(Camera & camera);
    virtual void draw();
private:
    GLuint vao;
    GLuint vbo;
    GLuint texture;
    GLuint program;
};
//--------------------------------------------------------------------------------------

#endif /* __CUBE_HPP */