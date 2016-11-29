#version 330
in vec3 position;
in vec3 normal;
in vec3 vertColor;
in vec2 textureCoord;

out vec2 texCoord;
out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragLight;

uniform vec3 offset;
uniform vec3 light;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 translate;

void main()
{
	fragNormal = (translate * vec4(normal, 1.0)).xyz;
	fragLight = light;
	texCoord = textureCoord;
	fragColor = vertColor;

	gl_Position = projectionMatrix * viewMatrix * (vec4(offset, 1.0) + (translate * vec4(position, 1.0)));
}