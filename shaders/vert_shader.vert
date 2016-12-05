#version 330
in vec3 position;
in vec3 normal;
in vec3 vertColor;

out vec3 fragColor;

uniform vec3 offset;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 translate;

void main()
{
	fragColor = vertColor;

	gl_Position = projectionMatrix * viewMatrix * (vec4(offset, 1.0) + (translate * vec4(position, 1.0)));
}