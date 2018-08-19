#version 120

varying vec2 tex_coord_0;

uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture2D(diffuse, tex_coord_0);
}
