#include "math.h"
#include <cmath>

bool areEqual(float a, float b, float epsilon)
{
	return (fabs(a - b) <= epsilon);
}
