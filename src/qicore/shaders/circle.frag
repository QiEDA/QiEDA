in vec4 vColor[];
in float radius;

void main(void)
{
	vec2 pos = mod(gl_FragCoord.xy, vec2(50.0)) - vec2(25.0);
	float dist_squared = dot(pos, pos);

	if( dist_squared < radius )
	{
		gl_FragColor = vColor[0];
	}
	else
	{
		discard;
	}
}
