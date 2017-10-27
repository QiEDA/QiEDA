#version 150 core

#define FLAGS_TYPE_FILLED_CIRCLE (1 << 0)
#define FLAGS_TYPE_HOLLOW_CIRCLE (1 << 1)
out vec4 color;

in vec4 vo_Color;
in vec2 vo_Position;

flat in vec4 vo_Params;
flat in int vo_Flags;

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

    if((vo_Flags & FLAGS_TYPE_FILLED_CIRCLE) == FLAGS_TYPE_FILLED_CIRCLE)
    {
        vec2 center = vec2(vo_Params[0], vo_Params[1]);
        float outerRadius = vo_Params[2];
        if(distanceSquared(vo_Position, center) > pow(outerRadius,2))
        {
            discard;
        }
    }
    else if((vo_Flags & FLAGS_TYPE_HOLLOW_CIRCLE) == FLAGS_TYPE_HOLLOW_CIRCLE)
    {
        vec2 center = vec2(vo_Params[0], vo_Params[1]);
        float outerRadius = vo_Params[2];
        float innerRadius = vo_Params[3];
        float sqrdDistance = distanceSquared(vo_Position, center);
        if(sqrdDistance > pow(outerRadius,2) ||
            sqrdDistance < pow(innerRadius,2) )
        {
            discard;
        }
    }
}