#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_uv;

out vec3 normal;
out vec3 lightDir;
out vec4 shadowCoord;

out vec4 worldPosition;

uniform mat4 M;
uniform mat4 MVP;
uniform mat4 cameraView;
uniform vec3 lightInvDir;

void main() {
	worldPosition = M * vec4(v_position, 1);
	gl_Position = MVP * vec4(v_position, 1);

	shadowCoord = vec4(v_position, 1);

	lightDir = (cameraView * vec4(lightInvDir, 0)).xyz;

	normal = (cameraView * M * vec4(v_normal, 0)).xyz;
}
