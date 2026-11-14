#version 330 core

out vec4 FragColor;

uniform vec2 uResolution;
uniform vec2 uCameraAngles;

uniform int atmosphereMode;

uniform vec3 solidColor;
uniform vec3 zenithColor;
uniform vec3 horizonColor;
uniform vec3 nadirColor;

// Two-color gradient
uniform float transitionPosition;
uniform float transitionWidth;

// Three-color gradient
uniform float upperTransitionPosition;
uniform float upperTransitionWidth;
uniform float lowerTransitionPosition;
uniform float lowerTransitionWidth;

uniform bool sunEnabled;
uniform vec3 sunColor;
uniform float sunAzimuth;
uniform float sunElevation;
uniform float sunIntensity;
uniform float sunGlare;
uniform float sunSize;

vec3 getSunDirection(float azimuth, float elevation)
{
    return normalize(vec3(
        cos(elevation) * sin(azimuth),
        sin(elevation),
        -cos(elevation) * cos(azimuth)
    ));
}

void main()
{
    vec2 uv = (gl_FragCoord.xy / uResolution) * 2.0 - 1.0;

    uv.x *= uResolution.x / uResolution.y;

    float yaw = radians(uCameraAngles.x);
    float pitch = radians(uCameraAngles.y);

    vec3 direction = normalize(vec3(uv.x, uv.y, -1.0));

    // pitch
    mat3 pitchRotation = mat3(
        1.0, 0.0, 0.0,
        0.0, cos(pitch), -sin(pitch),
        0.0, sin(pitch), cos(pitch)
    );

    // yaw
    mat3 yawRotation = mat3(
        cos(yaw), 0.0, sin(yaw),
        0.0, 1.0, 0.0,
        -sin(yaw), 0.0, cos(yaw)
    );

    direction = yawRotation * pitchRotation * direction;

    // gradient
    vec3 color;

    if (atmosphereMode == 0)
    {
        // Solid Color
        color = solidColor;
    }
    else if (atmosphereMode == 1)
    {
        // Two-Color Gradient
        float blend = smoothstep(
            transitionPosition - transitionWidth * 0.5,
            transitionPosition + transitionWidth * 0.5,
            direction.y
        );

        color = mix(nadirColor, zenithColor, blend);
    }
    else if (atmosphereMode == 2)
    {
        // Three-Color Gradient
        float lowerBlend = smoothstep(
            lowerTransitionPosition - lowerTransitionWidth * 0.5,
            lowerTransitionPosition + lowerTransitionWidth * 0.5,
            direction.y
        );

        float upperBlend = smoothstep(
            upperTransitionPosition - upperTransitionWidth * 0.5,
            upperTransitionPosition + upperTransitionWidth * 0.5,
            direction.y
        );

        vec3 lowerColor = mix(nadirColor, horizonColor, lowerBlend);

        color = mix(lowerColor, zenithColor, upperBlend);
    }

    // sun
    if (sunEnabled)
    {
        vec3 sunDirection = getSunDirection(sunAzimuth, sunElevation);

        float cosAngle = dot(direction, sunDirection);

        // Sun radius in radians
        float radius = radians(sunSize);

        float disk = smoothstep(
            cos(radius + radians(0.1)),
            cos(radius),
            cosAngle
        );

        color += sunColor * disk * sunIntensity;

        // Sun glare
        float glareRadius = radius * 5.0;

        float glow = 1.0 - smoothstep(
            radius,
            glareRadius,
            acos(clamp(cosAngle, -1.0, 1.0))
        );

        color += sunColor * glow * sunIntensity * sunGlare;
    }

    // fianlly apply color
    FragColor = vec4(color, 1.0);
}