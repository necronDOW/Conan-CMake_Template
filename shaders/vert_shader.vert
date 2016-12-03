#version 330
in vec3 position;
in vec3 vertColor;

out vec3 fragColor;

void main()
{
	 gl_Position = vec4(position, 1.0);
	 fragColor = vertColor;
}