#include "doublenumberssupport.h"

bool DoubleCompare::doubleEquals(double left, double right, double epsilon)
{
	return (fabs(left - right) < epsilon);
}

bool DoubleCompare::fuzzyIsNull(double value, double precision)
{
	return (fabs(0 - value) < precision);
}