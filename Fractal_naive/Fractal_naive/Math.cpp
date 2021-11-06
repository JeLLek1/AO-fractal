#include "Math.h"

size_t Math::get_pow_2(size_t n)
{
	size_t pow = 1;
	size_t tmp = n;
	//przesuniêcie bitowe podanej liczby a¿ do momentu kiedy bêdzie równa 1
	while (tmp > 1) {
		tmp = tmp >> 1;
		pow = pow << 1;
	}
	if (pow != n) {
		pow = pow << 1;
	}
	return pow;
}
