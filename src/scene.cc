#include "scene.hpp"
#include "application.hpp"

Scene::Scene(Application * _app){
    app = _app;
}
Scene::~Scene(){
}

void Scene::add_render_object(RenderObject * obj){
    render_objects.emplace_back(obj);
}

void Scene::set_camera(Camera * _camera){
    camera.reset(_camera);
}

void Scene::render_frame(){
    glClearColor(.9,.9,.9,.9);
    //glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (auto & obj : render_objects){
        obj->update(get_camera());
        obj->draw();
    }
}

void Scene::dispatch_key_pressed(int key){
    camera->handle_control(app->get_context().get_key_control(key));
}
void Scene::dispatch_scroll(double xoffset, double yoffset){
    camera->handle_control(app->get_context().get_scroll_control(xoffset, yoffset));
}