#version 430 core

layout (location = 0) in vec3 aPos;

layout (binding = 1, std430) readonly buffer modelMats {
    mat4 m_modelMatrices[];
};

out vec3 vPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
    vPos = aPos;

}
