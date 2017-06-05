#ifndef __RENDER_OBJECT_HPP
#define __RENDER_OBJECT_HPP

#include "gl_common.hpp"
#include "camera.hpp"

class RenderObject{
public:
    RenderObject() = default;
    virtual ~RenderObject(){}
    virtual void update(Camera & camera) = 0;
    virtual void draw() = 0;
    const glm::mat4 & get_local_matrix() const {return local_matrix;}
protected:
    void set_local_matrix(const glm::mat4 &lm){local_matrix = lm;}
    glm::mat4 local_matrix;
};

#endif /* __RENDER_OBJECT_HPP */