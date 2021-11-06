#include "RGBTable.h"

RGBTable::RGBTable(size_t size)
{
    colors_.resize(size);
    for (size_t i = 0; i < size; i++) {
        colors_[i] = Color::MakeFromHSV(i * 360.f / size, 1.f, 1.f, 1.f);
    }
}

GLfloat RGBTable::getR(size_t index)
{
	return colors_[index % colors_.size()].r;
}

GLfloat RGBTable::getG(size_t index)
{
    return colors_[index % colors_.size()].g;
}

GLfloat RGBTable::getB(size_t index)
{
    return colors_[index % colors_.size()].b;
}

std::vector<Color>& RGBTable::getColorsVector()
{
    return colors_;
}
