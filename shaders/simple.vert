#version 450

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

layout(location=2)uniform mat4 MVP;
layout(location=7) uniform vec3 camerPos;


layout(location=0) out vec3 fragNormal;
layout(location=1) out vec3 fragPosition;
layout(location=2) out vec3 fragCameraPosition;

void main() {
    vec4 mvp_pos = MVP * vec4(position ,1);
    gl_Position = mvp_pos;

    fragNormal = normal;
    fragPosition = (mvp_pos / mvp_pos.w).xyz;
    fragCameraPosition = camerPos;
}