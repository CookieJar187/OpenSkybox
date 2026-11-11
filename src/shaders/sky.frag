#version 330 core

out vec4 FragColor;

uniform vec2 uResolution;
uniform vec2 uCameraAngles;

uniform vec3 zenithColor = vec3(0.05, 0.25, 0.65);
uniform vec3 horizonColor = vec3(0.65, 0.80, 0.95);
uniform vec3 nadirColor = vec3(0.25, 0.35, 0.45);

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
    //vec3 zenithColor = vec3(0.05, 0.25, 0.65);
    //vec3 horizonColor = vec3(0.65, 0.80, 0.95);
    //vec3 nadirColor = vec3(0.25, 0.35, 0.45);

    vec3 color;

    if (direction.y >= 0.0)
    {
        color = mix(horizonColor, zenithColor, direction.y);
    }
    else
    {
        color = mix(horizonColor, nadirColor, -direction.y);
    }

    FragColor = vec4(color, 1.0);
}