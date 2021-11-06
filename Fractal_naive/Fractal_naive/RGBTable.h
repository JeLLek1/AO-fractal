#pragma once
#include "settings.h"
#include "Color.h"
#include <glad/glad.h>
#include <vector>

class RGBTable
{
protected:
	std::vector<Color> colors_;
public:
	RGBTable(size_t size);

	GLubyte getRub(size_t index);
	GLubyte getGub(size_t index);
	GLubyte getBub(size_t index);
};

