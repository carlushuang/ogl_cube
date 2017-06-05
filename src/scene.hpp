#ifndef __SCENE_HPP
#define __SCENE_HPP

#include "camera.hpp"
#include "render_object.hpp"
#include "event_handler.hpp"
#include <memory>
#include <vector>

class Application;

class Scene : public EventDispatcher{
public:
    Scene(Application * _app);
    virtual ~Scene();
    typedef std::vector<std::unique_ptr<RenderObject>> RenderVectorType;
    void add_render_object(RenderObject * obj);
    void render_frame();

    void set_camera(Camera * _camera);
    Camera & get_camera() {return *camera;}

    virtual void dispatch_key_pressed(int key);
    virtual void dispatch_scroll(double xoffset, double yoffset);
private:
    Application * app;
    RenderVectorType render_objects;
    std::unique_ptr<Camera>  camera;
};

#endif /* __SCENE_HPP */