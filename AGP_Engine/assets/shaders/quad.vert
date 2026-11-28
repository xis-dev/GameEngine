#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

// Camera: projection * view, uploaded once per frame
layout (location = 0) uniform mat4 uViewProj;

layout (binding = 0, std430) readonly buffer modelMats {
    mat4 m_modelMatrices[];
};

layout (location = 0) out vec3 vPos;
layout (location = 1) out vec2 vUV;

void main() {
    gl_Position = m_modelMatrices[gl_InstanceID] * vec4(aPos, 1.0);
    vPos = aPos;
    vUV = aUV;

}
