#version 150 core

out vec4 color;

in vec4 vo_Color;

void main(void)
{
    color = vo_Color;
}