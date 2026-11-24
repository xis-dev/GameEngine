#version 330 core

out vec4 oFragColour;

in vec3 vPos;

void main() {

    oFragColour = vec4(vPos, 1.0);
}