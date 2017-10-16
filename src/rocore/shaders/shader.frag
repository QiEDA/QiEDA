#version 150 core

#define OPTIONS_TYPE_FILLED_CIRCLE (1 << 0)
#define OPTIONS_TYPE_HOLLOW_CIRCLE (1 << 1)

uniform float un_OuterRadius;
uniform float un_InnerRadius;
uniform vec2 un_Center;
uniform int un_Options;


out vec4 color;

in vec4 vo_Color;
in vec2 vo_Position;

float distanceSquared(vec2 position, vec2 center)
{
    float tmpX = position.x - center.x;

    tmpX = tmpX*tmpX;

    float tmpY = position.y - center.y;

    tmpY = tmpY*tmpY;

    return tmpX + tmpY;
}

void main(void)
{
    color = vo_Color;

    if((un_Options & OPTIONS_TYPE_FILLED_CIRCLE) == OPTIONS_TYPE_FILLED_CIRCLE)
    {
        if(distanceSquared(vo_Position, un_Center) > pow(un_OuterRadius,2))
        {
            discard;
        }
    }
    else if((un_Options & OPTIONS_TYPE_HOLLOW_CIRCLE) == OPTIONS_TYPE_HOLLOW_CIRCLE)
    {
        float sqrdDistance = distanceSquared(vo_Position, un_Center);
        if(sqrdDistance > pow(un_OuterRadius,2) ||
            sqrdDistance < pow(un_InnerRadius,2) )
        {
            discard;
        }
    }
}