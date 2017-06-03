#include "cube.hpp"
#include "application.hpp"
#include "camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "utils.hpp"

/*
        +7--------+6
       /|        /|
     3+---------+2|
      | +4 - - -| +5
      |/        |/
     0+---------+1
*/
static const GLfloat cube_vertices[] = {
    /* position          texcord */
    // front.
    -1.0, -1.0,  1.0,    0.0, 0.0,    /* vert 0 */
     1.0, -1.0,  1.0,    1.0, 0.0,    /* vert 1 */
     1.0,  1.0,  1.0,    1.0, 1.0,    /* vert 2 */
    -1.0, -1.0,  1.0,    0.0, 0.0,    /* vert 0 */
     1.0,  1.0,  1.0,    1.0, 1.0,    /* vert 2 */
    -1.0,  1.0,  1.0,    0.0, 1.0,    /* vert 3 */
    // left
    -1.0, -1.0, -1.0,    0.0, 0.0,    /* vert 4 */
    -1.0, -1.0,  1.0,    1.0, 0.0,    /* vert 0 */
    -1.0,  1.0,  1.0,    1.0, 1.0,    /* vert 3 */
    -1.0, -1.0, -1.0,    0.0, 0.0,    /* vert 4 */
    -1.0,  1.0,  1.0,    1.0, 1.0,    /* vert 3 */
    -1.0,  1.0, -1.0,    0.0, 1.0,    /* vert 7 */
    // right
     1.0, -1.0,  1.0,    0.0, 0.0,    /* vert 1 */
     1.0, -1.0, -1.0,    1.0, 0.0,    /* vert 5 */
     1.0,  1.0, -1.0,    1.0, 1.0,    /* vert 6 */
     1.0, -1.0,  1.0,    0.0, 0.0,    /* vert 1 */
     1.0,  1.0, -1.0,    1.0, 1.0,    /* vert 6 */
     1.0,  1.0,  1.0,    0.0, 1.0,    /* vert 2 */
     // top
    -1.0,  1.0,  1.0,    0.0, 0.0,    /* vert 3 */
     1.0,  1.0,  1.0,    1.0, 0.0,    /* vert 2 */
     1.0,  1.0, -1.0,    1.0, 1.0,    /* vert 6 */
    -1.0,  1.0,  1.0,    0.0, 0.0,    /* vert 3 */
     1.0,  1.0, -1.0,    1.0, 1.0,    /* vert 6 */
    -1.0,  1.0, -1.0,    0.0, 1.0,    /* vert 7 */
    // bottom
    -1.0, -1.0, -1.0,    0.0, 0.0,    /* vert 4 */
     1.0, -1.0, -1.0,    1.0, 0.0,    /* vert 5 */
     1.0, -1.0,  1.0,    1.0, 1.0,    /* vert 1 */
    -1.0, -1.0, -1.0,    0.0, 0.0,    /* vert 4 */
     1.0, -1.0,  1.0,    1.0, 1.0,    /* vert 1 */
    -1.0, -1.0,  1.0,    0.0, 1.0,    /* vert 0 */
    // back
     1.0, -1.0, -1.0,    0.0, 0.0,    /* vert 5 */
    -1.0, -1.0, -1.0,    1.0, 0.0,    /* vert 4 */
    -1.0,  1.0, -1.0,    1.0, 1.0,    /* vert 7 */
     1.0, -1.0, -1.0,    0.0, 0.0,    /* vert 5 */
    -1.0,  1.0, -1.0,    1.0, 1.0,    /* vert 7 */
     1.0,  1.0, -1.0,    0.0, 1.0,    /* vert 6 */
};
#if 0
static const GLfloat cube_colors[] = {
    // front colors
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
    // back colors
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0
};

static const GLushort cube_elements[] = {
    // front
    0, 1, 2,
    2, 3, 0,
    // top
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // bottom
    4, 0, 3,
    3, 7, 4,
    // left
    4, 5, 1,
    1, 0, 4,
    // right
    3, 2, 6,
    6, 7, 3
};
#endif


Cube::Cube(Application * _app){
    app = _app;
    /* shaders */
    program = Utils::create_program({"res/cube.vs","res/cube.fs"});
    /* vao vbo ebo */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

    glBindVertexArray(0);

    /* texture */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#if 0
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_GREEN);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);
#endif

#if 0
    gli::texture gli_texture = gli::load("OpenGL_Tutorial_Texture.dds");
    if(gli_texture.empty()){
        std::cout<<"ERROR: can't load texture"<<std::endl;
        exit(EXIT_FAILURE);
    }
    //glm::tvec3<int> const gli_extent(gli_texture.extent());
    std::cout<<"gli_texture "<<"format:"<<gli_texture.format()
        <<" w:"<<gli_texture.extent().x<<" h:"<<gli_texture.extent().y
        <<" compressed:"<<gli::is_compressed(gli_texture.format())
        <<std::endl
        <<" target:"<<gli_texture.target()<<" size:"<<gli_texture.size()
        <<" faces:"<<gli_texture.faces()<<" layers:"<<gli_texture.layers()<<" levels:"<<gli_texture.levels()
        <<std::endl;

    gli::gl GL(gli::gl::PROFILE_GL33);
    gli::gl::format const GL_Format = GL.translate(gli_texture.format(), gli_texture.swizzles());
    GLenum GL_Target = GL.translate(gli_texture.target());
    std::cout<<"GL translate"<<" target:"<<GL_Target<<" format:"<<GL_Format.Internal<<std::endl;
    // https://stackoverflow.com/questions/27200528/loading-an-uncompressed-dds-to-gl-texture
    // internal format use GL_BGRA
    if(gli::is_compressed(gli_texture.format())){
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_Format.Internal, gli_texture.extent().x, gli_texture.extent().y,
            0, gli_texture.size(), gli_texture.data());
    }else{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_Format.Internal, gli_texture.extent().x, gli_texture.extent().y,
            0, GL_BGRA, GL_UNSIGNED_BYTE, gli_texture.data());
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    //std::cout<<"end of Cube"<<std::endl;

#endif
    int width, height, nrComponents;
    // opengl will map texture upside down, hence we need flip back
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("res/OpenGL_Tutorial_Texture.jpg", &width, &height, &nrComponents, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    // init model matrix
    mat_model = glm::mat4(1.0f);

    // NOTICE:the difference!
    // mat1 = rotate(mat2,radians(r), vec3(1,0,0));
    // not equale to
    // mat1 = mat2 * mat_r  (mat_r : rotated degree matrix)
    //mat_model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0,1,0)) * mat_model;
    //std::cout<<"model matrix:"<<std::endl; dump_mat4(mat_model);
}

Cube::~Cube(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glDeleteProgram(program);
    glDeleteTextures(1, &texture);
    std::cout<<"Cube dtor"<<std::endl;
}

void Cube::draw(){

    glUseProgram(program);

    glm::mat4 mat_mvp = app->get_camera().update_proj_view()*mat_model;

    glUniformMatrix4fv(glGetUniformLocation(program, "mat_mvp"), 1, GL_FALSE, glm::value_ptr(mat_mvp));

    glUniform1i(glGetUniformLocation(program, "cube_texture"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(cube_vertices)/sizeof(cube_vertices[0]));
    //glDrawArrays(GL_TRIANGLES, 0, 3);
}