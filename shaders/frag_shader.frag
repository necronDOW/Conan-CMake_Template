#version 330
out vec4 outputColor;

in vec2 texCoord;
in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragLight;

uniform sampler2D tex;

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 L = normalize(fragLight);
	float dIntensity = 1.0; //max(dot(N, L), 0.0);
	vec4 diffuseColor = vec4(dIntensity, dIntensity, dIntensity, 1.0);

	outputColor = diffuseColor * vec4(fragColor, 1.0f) * texture(tex, texCoord);
}