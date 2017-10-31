#version 150 core

#define FLAGS_TYPE_FILLED_CIRCLE (1 << 0)
#define FLAGS_TYPE_HOLLOW_CIRCLE (1 << 1)
#define FLAGS_TYPE_LINE          (1 << 2)
#define FLAGS_TYPE_FILLED_ARC    (1 << 3)
#define FLAGS_TYPE_LINE_ARC      (1 << 4)
#define FLAGS_TYPE_GRID (1 << 10)
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
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

/*
 * Borrowed function from https://github.com/rreusser/glsl-solid-wireframe
 * © Ricky Reusser 2016. MIT License.
 */
float gridFactor(vec2 parameter, float width) {
    vec2 d = fwidth(parameter);
    vec2 looped = 0.5 - abs(mod(parameter, 1.0) - 0.5);
    vec2 a2 = smoothstep(d * (width - 0.5), d * (width + 0.5), looped);

    return min(a2.x, a2.y);
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
    else if((vo_Flags & FLAGS_TYPE_HOLLOW_CIRCLE) == FLAGS_TYPE_HOLLOW_CIRCLE ||
        (vo_Flags & FLAGS_TYPE_LINE_ARC) == FLAGS_TYPE_LINE_ARC)
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
    else if((vo_Flags & FLAGS_TYPE_GRID) == FLAGS_TYPE_GRID)
    {
        float cartesianX = 1/vo_Params[0];
        float cartesianY = 1/vo_Params[1];

        float g = gridFactor(vec2(
                               cartesianX > 0.0 ? vo_Position.x * cartesianX : 0.5,
                               cartesianY > 0.0 ? vo_Position.y * cartesianY : 0.5
                             ), 1.0);

        color = vec4(mix(vec3(vo_Color.xyz), vec3(0), g), vo_Color.a);
    }
}