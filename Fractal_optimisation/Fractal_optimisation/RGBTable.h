#pragma once
#include "settings.h"
#include "Color.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class RGBTable
{
protected:
	std::vector<Color> colors_;
	std::vector<GLubyte> colorsub_;
public:
	RGBTable(size_t size);

	GLubyte getRub(size_t index);
	GLubyte getGub(size_t index);
	GLubyte getBub(size_t index);

	std::vector<GLubyte>& getColorsVectorub();
	size_t getColorsVectorubSize();

	std::vector<Color>& getColorsVector();
	size_t getColorsVectorSize();
};

