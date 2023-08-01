#version 410 core
layout (location = 0) in vec3 vertex;
out vec3 vpos;
void main()
{
    vpos = vertex + vec3(0.5, 0.5, 0);
    gl_Position = vec4(vertex, 1.0);
}