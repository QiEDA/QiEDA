#version 150 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec4 vi_Color;

in vec3 vi_VertexPos;

out vec4 vo_Color;

void main(void)
{
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vi_VertexPos,1.0);
    vo_Color = vi_Color;
}