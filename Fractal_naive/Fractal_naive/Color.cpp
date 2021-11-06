#include "Color.h"
#include <cmath>

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color& Color::operator=(const Color& right)
{
    this->r = right.r;
    this->g = right.g;
    this->b = right.b;
    this->a = right.a;
    return *this;
}

Color Color::MakeFromHSV(GLfloat H, GLfloat S, GLfloat V, GLfloat a)
{
	//konwersja wed³ug wzoru http://4.bp.blogspot.com/-BIcNZkeJHn0/T94CP7e0F3I/AAAAAAAAAP8/ZX7vnhdklV8/s1600/hsvtorgb.png
	float c, m, x, cm, xm, r, g, b;
	c = V * S;
	m = V - c;
	x = c * (1 - std::fabs(std::fmod((H / 60.f), 2.f) - 1));
	cm = c + m;
	xm = x + m;
	int part = static_cast<int>(H / 60);
	switch (part) {
	case 0:
		r = cm, g = xm, b = m;
		break;
	case 1:
		r = xm, g = cm, b = m;
		break;
	case 2:
		r = m, g = cm, b = xm;
		break;
	case 3:
		r = m, g = xm, b = cm;
		break;
	case 4:
		r = xm, g = m, b = cm;
		break;
	case 5:
		r = cm, g = m, b = xm;
		break;
	default:
		r = m, g = m, b = m;
		break;
	}

	return Color(r, g, b, a);
}
