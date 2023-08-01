#version 410 core

in vec3 vpos;
out vec4 outColor;
uniform vec3 color = vec3(0.0);

void main()
{
    outColor = vec4(vpos * color, 1.0);
}