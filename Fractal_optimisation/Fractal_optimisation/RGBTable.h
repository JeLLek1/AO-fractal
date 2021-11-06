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
public:
	RGBTable(size_t size);

	GLfloat getR(size_t index);
	GLfloat getG(size_t index);
	GLfloat getB(size_t index);

	std::vector<Color>& getColorsVector();
};

