#ifndef __MODEL_HPP
#define __MODEL_HPP

#include <vector>
#include "mesh.hpp"
#include <unordered_map>

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#define V3_CPY(v_des, v_src) do{\
    (v_des).x=(v_src).x; (v_des).y=(v_src).y; (v_des).z=(v_src).z;}while(0)
#define V2_CPY(v_des, v_src) do{\
    (v_des).x=(v_src).x; (v_des).y=(v_src).y; }while(0)

class Model{
public:
    typedef std::unordered_map<std::string, GLuint> TexMapType;
    TexMapType texture_map;
    //std::vector<Texture> textures;
    std::vector<Mesh> meshes;
    std::string path;
    std::string name;
    bool loaded;
    Model(std::string model_file);
    virtual ~Model();

    static GLuint gen_texture(std::string  tex_file);
    void dump_model();
private:
    void load_model(const std::string model_file);

    void parse_node(const aiScene* scene, const aiNode * node);
    void parse_mesh(const aiScene* scene, const aiMesh * mesh);
};

#endif /* __MODEL_HPP */