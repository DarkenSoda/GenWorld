#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vertexNormal;
out vec3 vertexColor;
out vec2 vertexTexCoord;
out vec3 WorldPos;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    vertexNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vertexColor = aColor;
    vertexTexCoord = aTexCoord;

    WorldPos = vec3(uModel * vec4(aPos, 1.0));
}
