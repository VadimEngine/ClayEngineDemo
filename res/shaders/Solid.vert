#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout(std140) uniform Camera {
    mat4 view;
    mat4 projection;
};

uniform mat4 uModel;
uniform mat4 uScaleMat;

void main() {
    gl_Position = projection * view * uModel * uScaleMat * vec4(aPos, 1.0);
}