#version 120

attribute vec3 position;
attribute vec2 tex_coord;
attribute vec3 normal;

varying vec2 tex_coord_0;
varying vec3 normal_0;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    tex_coord_0 = tex_coord;
    normal_0 = (mvp * vec4(normal, 0.0)).xyz;
}
