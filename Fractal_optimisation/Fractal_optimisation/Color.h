#pragma once
#include <glad/glad.h>
#pragma pack(push, 1)
class Color
{
public:
    GLfloat r, g, b, a;

    Color(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 0.0f);
    Color& operator =(const Color& right);

    static Color MakeFromHSV(GLfloat H, GLfloat S, GLfloat V, GLfloat a);
};
#pragma pack(pop)

