#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 UV;

uniform sampler2D tex;

void main(){
    FragColor = texture(tex, UV);
}
