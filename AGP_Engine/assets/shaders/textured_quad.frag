#version 430 core

layout (location = 0) out vec4 oFragColour;

layout (location = 0) in vec3 vFragPos;
layout (location = 1) in vec2 vUV;

void main() {
    oFragColour = vec4(vFragPos, 1.0);
}