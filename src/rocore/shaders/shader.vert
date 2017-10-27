#version 150 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
uniform vec4 vi_Color;

in vec3 vi_VertexPos;
in vec4 vi_Params;
in int vi_Flags;

out vec4 vo_Color;
out vec2 vo_Position;
flat out vec4 vo_Params;
flat out int vo_Flags;

void main(void)
{
    gl_Position = mvpMatrix * vec4(vi_VertexPos,1.0);
    vo_Color = vi_Color;
    vo_Position = vi_VertexPos.xy;
    vo_Params = vi_Params;
    vo_Flags = vi_Flags;
}