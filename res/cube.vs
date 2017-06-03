#version 330 core

layout (location=0) in vec3 in_position;
layout (location=1) in vec2 in_tex_cord;

uniform mat4 mat_mvp;

out vec2 vs_tex_cord;

void main()
{
    gl_Position = mat_mvp * vec4(in_position,1.0f);
    //gl_Position = vec4(in_position,1.0f);
    vs_tex_cord = in_tex_cord;
}
