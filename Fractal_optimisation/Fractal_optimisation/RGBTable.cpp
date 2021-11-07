#include "RGBTable.h"

RGBTable::RGBTable(size_t size)
{
    colors_.resize(size);
    colorsub_.resize(size * 3);
    for (size_t i = 0; i < size; i++) {
        colors_[i] = Color::MakeFromHSV(i * 360.f / size, 1.f, 1.f, 1.f);
        colorsub_[i * 3] = static_cast<GLubyte>(colors_[i].r * 255);
        colorsub_[i * 3 + 1] = static_cast<GLubyte>(colors_[i].g * 255);
        colorsub_[i * 3 + 2] = static_cast<GLubyte>(colors_[i].b * 255);
    }
}

GLubyte RGBTable::getRub(size_t index)
{
	return colorsub_[index % colors_.size() * 3];
}

GLubyte RGBTable::getGub(size_t index)
{
    return colorsub_[index % colors_.size() * 3 + 1];
}

GLubyte RGBTable::getBub(size_t index)
{
    return colorsub_[index % colors_.size() * 3 + 2];
}

std::vector<GLubyte>& RGBTable::getColorsVectorub()
{
    return colorsub_;
}

size_t RGBTable::getColorsVectorubSize()
{
    return colorsub_.size() * sizeof(GLubyte);
}

std::vector<Color>& RGBTable::getColorsVector()
{
    return colors_;
}

size_t RGBTable::getColorsVectorSize()
{
    return colors_.size() * sizeof(Color);
}
