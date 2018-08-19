#version 120

attribute vec3 position;
attribute vec2 tex_coord;

varying vec2 tex_coord_0;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(position, 1.0);
    tex_coord_0 = tex_coord;
}
