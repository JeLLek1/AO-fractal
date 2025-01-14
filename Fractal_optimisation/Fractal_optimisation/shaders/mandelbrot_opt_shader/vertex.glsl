#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

out vec4 color;
out vec2 UV;
out vec2 pos;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = color;
    UV = aUV;
}
