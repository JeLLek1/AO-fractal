#include "RGBTable.h"

RGBTable::RGBTable(size_t size)
{
    colors_.resize(size);
    for (size_t i = 0; i < size; i++) {
        colors_[i] = Color::MakeFromHSV(i * 360.f / size, 1.f, 1.f, 1.f);
    }
}

GLubyte RGBTable::getRub(size_t index)
{
	return static_cast<GLubyte>(colors_[(index % colors_.size())].r * 255);
}

GLubyte RGBTable::getGub(size_t index)
{
    return static_cast<GLubyte>(colors_[(index % colors_.size())].g * 250);
}

GLubyte RGBTable::getBub(size_t index)
{
    return static_cast<GLubyte>(colors_[(index % colors_.size())].b * 250);
}
