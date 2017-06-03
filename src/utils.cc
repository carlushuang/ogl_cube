#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>

//using namespace Utils;

std::string Utils::get_file_data(const std::string &file_path){
    std::ifstream file (file_path);
    if(!file){  // operator bool()  c++11
        std::cout<<"error reading file from path:"<<file_path<<std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                  (std::istreambuf_iterator<char>())  );
}

GLuint Utils::create_program(const std::initializer_list<std::string> & shaders){
    std::vector<GLuint> shader_ids;
    GLuint program;
    GLint status=0;
    for(const std::string &shader : shaders){
        std::string extension;
        GLenum shaderType;
        GLuint id;
        GLint status=0;

        extension = shader.substr(shader.find_last_of(".") + 1);
        if(extension == "vs" || extension == "vert"){
            shaderType = GL_VERTEX_SHADER;
        }else if(extension == "fs" ||extension == "frag"){
            shaderType = GL_FRAGMENT_SHADER;
        }
        id = glCreateShader(shaderType);
        std::string _str=Utils::get_file_data(shader);
        const char * data =_str.c_str();
        //std::cout<<data<<std::endl;
        glShaderSource(id, 1, &data, nullptr);
        glCompileShader(id);
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if(status ==  GL_FALSE){
            GLchar * log;
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            log = new GLchar[maxLength];
            if(!log){
                ;
            }
            else{
                glGetShaderInfoLog(id, maxLength, NULL, log);
                std::cout<<"error while compile shader "<<shader<<std::endl<<log<<std::endl;
                delete[] log;
            }
            exit(EXIT_FAILURE);
        }
        shader_ids.push_back(id);
    }
    program = glCreateProgram();
    for(GLuint shader_id: shader_ids)
        glAttachShader(program, shader_id);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status){
        std::cout<<"error while link program"<<std::endl;
        for(GLuint shader_id: shader_ids)
            glDeleteShader(shader_id);
        glDeleteProgram(program);
        exit(EXIT_FAILURE);
    }

    for(GLuint shader_id: shader_ids)
        glDeleteShader(shader_id);

    return program;
}

GLuint Utils::create_program(const std::string &shader){
    return Utils::create_program({shader});
}

void Utils::dump_mat4(const glm::mat4 & mat){
    int i,j;
    for(i=0;i<4;i++){
        std::cout<<"  ";
        for(j=0;j<4;j++){
            std::cout<<mat[i][j]<<"\t";
        }
        std::cout<<"\r\n";
    }
}