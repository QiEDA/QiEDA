#version 120

uniform vec2 iCenter;

varying vec4 circleOrigin;

void main()
{
  gl_Position = ftransform();
  circleOrigin = vec4(iCenter,0,0) * gl_ModelViewMatrix;
}