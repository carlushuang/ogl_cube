#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include "gl_common.hpp"
#include <vector>
#include <memory>

struct Texture{
    GLuint id;
    unsigned int type;
    std::string path;   // should be relative to model::path
};

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 texcord;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    GLuint VAO;

    Mesh();
    virtual ~Mesh();
private:

};

#endif /* MESH_HPP */
