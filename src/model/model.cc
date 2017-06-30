#include "model.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Model::Model(std::string model_file):loaded(false){
    size_t split = model_file.find_last_of('/');
    if( split ==  std::string::npos){
        path.clear();
        split = 0;
    }
    else{
        split ++;
        path = model_file.substr(0, split);    //within last /
    }
    name = model_file.substr(split);
    load_model(model_file);
    //dump_model();
}
Model::~Model(){
    
}

void Model::load_model(const std::string model_file){
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile( model_file,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return ;
    }

    parse_node(scene, scene->mRootNode);
    loaded = true;
}

void Model::dump_model(){
    if(!loaded){
        std::cerr<<"ERROR:: model not load properly"<< std::endl;
        return;
    }
    std::cout<<"Model: "<<path+name<<std::endl;
    for(auto & mesh: this->meshes){
        std::cout<<"  mesh: v:"<<mesh.vertices.size()
                 <<" i:"<<mesh.indices.size()<<std::endl;
        for(auto & tex: mesh.textures){
            std::cout<<"      texture:"<<tex.path<<" type:"<<tex.type<<" id:"<<tex.id<<std::endl;
        }
    }

    for(auto & itr: this->texture_map){
        std::cout<<"  texture:"<<itr.first<<" id:"<<itr.second<<std::endl;
    }
}

void Model::parse_mesh(const aiScene* scene, const aiMesh * mesh){
    aiMaterial * mat;
    //assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
    Mesh m;
    unsigned int i;
    //std::cout<<"new mesh, vert:"<<mesh->mNumVertices<<" "<<mesh->HasPositions()<<std::endl;
    for(i=0;i<mesh->mNumVertices;i++){
        Vertex v;
        if(mesh->HasPositions())
            V3_CPY(v.position,  mesh->mVertices[i]);
        if(mesh->HasNormals())
            V3_CPY(v.normal,    mesh->mNormals[i]);
        if(mesh->HasTangentsAndBitangents()){
            V3_CPY(v.tangent,   mesh->mTangents[i]);
            V3_CPY(v.bitangent, mesh->mBitangents[i]);
        }

        if(mesh->GetNumUVChannels()>1){
            std::cerr << "WARNING! unsupport multi uv channel" <<std::endl;
            return ;
        }
        // Texture Coordinates
        if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            V2_CPY(v.texcord, mesh->mTextureCoords[0][i]);
        }
        else
            v.texcord = glm::vec2(0.0f, 0.0f);

        // feed vertices
        m.vertices.push_back(v);
    }

    // index
    for(i=0; i<mesh->mNumFaces; i++){
        aiFace *face = &mesh->mFaces[i];
        unsigned int j;
        for(j=0;j<face->mNumIndices;j--)
            m.indices.push_back(face->mIndices[j]);
    }

    // material
    mat = scene->mMaterials[mesh->mMaterialIndex];
    unsigned int type;
    for(type=aiTextureType_NONE;type<=aiTextureType_UNKNOWN;type++){
        unsigned int index;
        for(index=0;index<mat->GetTextureCount((aiTextureType)type);index++){
            aiString relative_path;
            mat->GetTexture((aiTextureType)type, index, &relative_path);
            std::string tex_path = relative_path.C_Str();
            //std::cout<<"  type:"<<type<<" index:"<<index<<" path:"<<path.C_Str()<<std::endl;
            TexMapType::const_iterator itr = this->texture_map.find(tex_path);
            Texture tex;
            if(itr == texture_map.end()){
                tex.id = gen_texture(this->path+tex_path);
                tex.type = type;
                tex.path = tex_path;
                this->texture_map.insert(std::make_pair(tex_path, tex.id));
                //m.texture_key.push_back(tex_path);
            } else {
                tex.id = itr->second;
                tex.type = type;
                tex.path = tex_path;
            }
            m.textures.push_back(tex);
        }
    }

    this->meshes.push_back(m);
}

void Model::parse_node(const aiScene* scene, const aiNode * node){
    unsigned int i;
    for(i=0;i<node->mNumMeshes;i++){
        parse_mesh(scene, scene->mMeshes[node->mMeshes[i]]);
    }
    for(i=0;i<node->mNumChildren;i++){
        parse_node(scene, node->mChildren[i]);
    }
}

GLuint Model::gen_texture(std::string  tex_file){
    int width, height, nrComponents;
     GLuint id=-1;
    // opengl will map texture upside down, hence we need flip back
    //std::cout<<"tex file:"<<tex_file<<std::endl;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(tex_file.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }
    else
    {
        std::cerr<<"Failed to load texture"<<tex_file<<std::endl;
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    return id;
}