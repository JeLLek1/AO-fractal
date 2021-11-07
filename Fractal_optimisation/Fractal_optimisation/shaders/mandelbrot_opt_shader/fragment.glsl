#version 460 core

layout(location = 0) out vec4 FragColor;
layout(std430, binding = 0) buffer ssboLayout
{
    vec4 colorsTable[];
};

in vec4 color;
in vec2 UV;

uniform uint maxLevels;
uniform uint maxColors;
uniform dvec2 ltCorner;
uniform double ratio;

void main(){
    double c_im = ratio * double(gl_FragCoord.y) + ltCorner.y;
    double c_re = ratio * double(gl_FragCoord.x) + ltCorner.x;

    uint level = 0;
    double z_re = 0, z_im = 0, tmp_re;

    do {
        tmp_re = z_re * z_re - z_im * z_im + c_re;
        z_im = c_im + 2 * z_re * z_im;
        z_re = tmp_re;

        level++;
    } while (z_re * z_re + z_im * z_im < 4 && level < maxLevels);
    if(level == maxLevels){
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }else{
        FragColor = colorsTable[level % maxColors];
    }
}
