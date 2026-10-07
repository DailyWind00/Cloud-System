#version 420 core

out vec4 Color;

uniform vec3 uCamPos;

uniform mat4 uInvView;
uniform mat4 uInvProj;

uniform vec2 uScreenSize;

uniform vec3 uCloudMin;
uniform vec3 uCloudMax;

layout(binding = 1) uniform sampler3D uWorleyTexture;

vec3 getRayDirection()
{
    vec2 uv = gl_FragCoord.xy / uScreenSize;

	// [0, 1] -> [-1, 1]
    vec2 ndc;
    ndc.x = uv.x * 2.0 - 1.0;
    ndc.y = uv.y * 2.0 - 1.0;

    vec4 clipPosition;
    clipPosition.x = ndc.x;
    clipPosition.y = ndc.y;
    clipPosition.z = 1.0;
    clipPosition.w = 1.0;

	// NDC -> view space
    vec4 viewPosition = uInvProj * clipPosition;

    viewPosition.xyz /= viewPosition.w;

	// View space -> world space
    vec4 worldDirection =
        uInvView * vec4(
            viewPosition.x,
            viewPosition.y,
            viewPosition.z,
            0.0
        );

    return normalize(worldDirection.xyz);
}

vec2 rayBoxIntersection(vec3 rayOrigin, vec3 rayDirection)
{
    vec3 invDir = 1.0 / rayDirection;

    vec3 t0 = (uCloudMin - rayOrigin) * invDir;
    vec3 t1 = (uCloudMax - rayOrigin) * invDir;

    vec3 tMin = min(t0, t1);
    vec3 tMax = max(t0, t1);

    float tEnter = max(
        max(tMin.x, tMin.y),
        tMin.z
    );

    float tExit = min(
        min(tMax.x, tMax.y),
        tMax.z
    );

    return vec2(tEnter, tExit);
}

float getHeight(vec3 position)
{
    return (position.y - uCloudMin.y) / (uCloudMax.y - uCloudMin.y);
}

float getHeightDensity(float height)
{
    float bottom = smoothstep(0.0, 0.2, height);
    float top = 1.0 - smoothstep(0.7, 1.0, height);

    return bottom * top;
}

float getDensity(vec3 position)
{
    float height = getHeight(position);

    float heightDensity = getHeightDensity(height);

    // World position -> [0, 1] cloud-local coordinates
    vec3 uvw = (position - uCloudMin) / (uCloudMax - uCloudMin);

    float worley = texture(uWorleyTexture, uvw * 0.25).r;

    // For now, use Worley as a density mask
    float noiseDensity = 1.0 - worley;

    return heightDensity * noiseDensity;
}

void main()
{
    vec3 rayOrigin = uCamPos;
    vec3 rayDirection = getRayDirection();

    vec2 intersection = rayBoxIntersection(
        rayOrigin,
        rayDirection
    );

    float tEnter = intersection.x;
    float tExit = intersection.y;

    if (tEnter > tExit || tExit < 0.0)
    {
        discard;
    }

    tEnter = max(tEnter, 0.0);

    const float stepSize = 0.01;
	const int maxSteps = 512;
	float density = 0;
	float t = tEnter;

	for (int i = 0; i < maxSteps && t < tExit; i++)
	{
		vec3 position = rayOrigin + rayDirection * t;

		float sampleDensity = getDensity(position);

		density += sampleDensity * stepSize;

		t += stepSize;
	}

	density /= maxSteps;
	density *= 100;

	// Color = vec4(vec3(density), 1.0);
	Color = vec4(density);
}