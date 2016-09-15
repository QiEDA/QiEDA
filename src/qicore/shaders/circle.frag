#version 120

varying vec4 circleOrigin;

void main (void)
{
    vec4 loc = gl_FragCoord;

    float radius=length(loc-circleOrigin);
    if(radius < 100.0)
    {
        gl_FragColor = vec4(1,0,0,1);
    }
    else
    {
        discard;
    }
}