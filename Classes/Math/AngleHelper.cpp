#include "AngleHelper.h"
#include "AngleUnwrapper.h"
#include <math.h>

// angleA = 3
// angleB = 200
// 
float AngleHelper::getSmallestDifference(float angleA, float angleB)
{
	angleA = AngleUnwrapper::unwrap(angleA);
	angleB = AngleUnwrapper::unwrap(angleB);
	float phi = fmod(angleB - angleA, 360.0f);       // This is either the distance or 360 - distance
	float distance = fabs(phi) > 180.0f ? 360.0f - fabs(phi) : phi;
	if (phi > 180.0f)
	{
		distance = -distance;
	}
	return distance;
}
