#version 330 core

in vec3 normal;
in vec3 lightDir;
in vec4 shadowCoord;

out vec3 color;

const float bias = 0.001;

in vec4 worldPosition;

uniform sampler2D shadowMap0;
uniform sampler2D shadowMap1;
uniform sampler2D shadowMap2;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform float cascadeLengths[3];
uniform mat4 depthBiasVPs[3];
uniform vec3 cameraPos;
uniform vec3 fogColor;
uniform vec3 lightColor;
uniform float fogIntensity;
uniform float fogHeight;
uniform float fogSpread;
uniform float nearPlaneDist;
uniform float farPlaneDist;
uniform mat4 cameraView;
uniform mat4 ditherMatrix;

float whenGreater(float x, float y) {
	return max(sign(x - y), 0.0);
}

float whenLess(float x, float y) {
	return max(sign(y - x), 0.0);
}

int getCascade(vec3 worldPos) {
	vec4 cameraPos = cameraView * vec4(worldPos, 1);

	float z = abs((cameraPos.z - nearPlaneDist) / (farPlaneDist - nearPlaneDist));

	float cascade = 1.0 * whenGreater(z, cascadeLengths[1])
		+ 1.0 * whenGreater(z, cascadeLengths[2]);
	return int(cascade);
}

float getR(int casc, vec3 pos) {
	if (casc == 0) {
		return texture(shadowMap0, pos.xy).r;
	}
	else if (casc == 1) {
		return texture(shadowMap1, pos.xy).r;
	}
	else {
		return texture(shadowMap2, pos.xy).r;
	}
}

void main() {
	vec3 startPos = cameraPos;
	vec3 endPos = vec3(worldPosition);

	vec3 rayVector = endPos - startPos;

	float rayLength = length(rayVector);
	vec3 rayDir = rayVector / rayLength;

	int steps = 100;
	float stepLength = rayLength / steps;

	vec3 stepVec = rayDir * stepLength;

	vec3 currentPos = startPos + vec3(ditherMatrix * vec4(stepVec, 1));

	float fog;
	for (int i = 0; i < steps; i++) {
		int casc = getCascade(currentPos);

		vec4 shadowPos = depthBiasVPs[casc] * vec4(currentPos, 1);

		float p = pow(max((fogHeight - currentPos.y) / fogHeight, 0), fogSpread);

		fog += whenGreater(getR(casc, shadowPos.xyz), shadowPos.z) * fogIntensity * p * stepLength / 100.0;

		currentPos += stepVec;
	}
	fog = clamp(fog, 0, 1);

	int shadowCascade = getCascade(vec3(worldPosition));
	vec4 realShadowCoord = depthBiasVPs[shadowCascade] * worldPosition;

	float visibility = 1.0 - 0.75 * whenLess(getR(shadowCascade, realShadowCoord.xyz), realShadowCoord.z - bias);

	vec3 n = normalize(normal);
	vec3 l = normalize(lightDir);
	float cosTheta = clamp(dot(n, l), 0, 1);

	color = (ambientColor
		+ visibility * diffuseColor * lightColor * cosTheta) * (1 - fog)
		+ fog * fogColor * lightColor;
}
