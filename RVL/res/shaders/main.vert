#version 330 core

in vec3 position;
in vec3 color;

out vec3 out_color;

void main()
{
    out_color = color;
    gl_Position = vec4(position, 1.0);
}
