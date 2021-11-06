#pragma once
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Vector2.h"

struct Character {
    unsigned int textureID = 0; // ID handle of the glyph texture
    Vector2<int> size;          // Size of glyph
    Vector2<int> bearing;       // Offset from baseline to left/top of glyph
    signed long advance = 0;    // Offset to advance to next glyph
};

class Font
{
protected:
    FT_Library ft_;
    std::map<char, Character> characters_;
public:
    Font(const char* fontSrc, FT_UInt fontSize);
    void operator=(const Font&) = delete;

    Character getCharacter(char c);
};

