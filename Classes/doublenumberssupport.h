#ifndef DOUBLENUMBERSSUPPORT_H
#define DOUBLENUMBERSSUPPORT_H

#include <cmath>

namespace DoubleCompare
{
	constexpr double DefaultEpsilon{ 0.0000001 };

	bool doubleEquals(double left, double right, double epsilon = DefaultEpsilon);
	bool fuzzyIsNull(double value, double precision = DefaultEpsilon);
}

#endif

