#version 330 core

in vec2 vs_tex_cord;
out vec4 color;

uniform sampler2D cube_texture;

void main(){
    color = texture(cube_texture, vs_tex_cord);
    //color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}
