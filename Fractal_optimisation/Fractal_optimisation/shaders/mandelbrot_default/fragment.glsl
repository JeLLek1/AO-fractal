#version 460 core

layout(location = 0) out vec4 FragColor;

in vec4 color;
in vec2 UV;

uniform sampler2D tex;

void main(){
    FragColor = texture(tex, UV);
}
