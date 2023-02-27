#include "../includes/cube3d.h"

void reset_360(float *val)
{
	if (*val < 0)
		*val += (2 * PI);
	if (*val > (2 * PI))
		*val -= (2 * PI);
	return ;
}

double hyp_dist(float ax, float ay, float bx, float by)
{
	float a;
	float b;

	a = (bx - ax) * (bx- ax);
	b = (by - ay) * (by - ay);
	return (sqrt(a + b));
}