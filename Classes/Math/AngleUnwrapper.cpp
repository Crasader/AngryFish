#include "AngleUnwrapper.h"
#include <math.h>

float AngleUnwrapper::unwrap(float degrees)
{
	if (degrees >= 0) {
		float tempAngle = fmod(degrees, 360.0f);
		return tempAngle == 360 ? 0 : tempAngle;
	}
	else
		return 360 - fmod((-1 * degrees), 360.0f);
}
