#version 420 core

out vec4 Color;

uniform vec3 uCamPos;

uniform mat4 uInvView;
uniform mat4 uInvProj;

uniform vec2 uScreenSize;

uniform vec3 uCloudMin;
uniform vec3 uCloudMax;

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
        Color = vec4(1.0);
        return;
    }

    tEnter = max(tEnter, 0.0);

    const float stepSize = 0.01;

    float steps = 0.0;

	for (float t = tEnter; t < tExit; t += stepSize)
	{
		vec3 position = rayOrigin + rayDirection * t;

		// Cloud density will eventually be calculated here.
		
		steps++;
	}

    // Visualize number of steps.
    float value = steps / 100.0;

    Color = vec4(vec3(value), 1.0);
}