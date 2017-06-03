#ifndef __UTILS_HPP
#define __UTILS_HPP

#include "gl_common.hpp"
#include <string>
#include <initializer_list>

namespace Utils{
    std::string get_file_data(const std::string &file_path);
    GLuint create_program(const std::initializer_list<std::string> & shaders);
    GLuint create_program(const std::string &shader);
    void dump_mat4(const glm::mat4 & mat);
}

#endif  /* __UTILS_HPP */