# version 420 core

in vec2 vUV;

out vec4 Color;

uniform vec3 uCamPos;
uniform mat4 uView;
uniform mat4 uProj;
uniform vec3 uCloudMin;
uniform vec3 uCloudMax;

void	main() {
	Color = vec4(1.0, 1.0, 1.0, 1.0);
}