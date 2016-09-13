in vec4 color;
out vec4 vColor;

void main(void)
{
	gl_Position = ftransform();
	vColor = color;
}