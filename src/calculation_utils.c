#include "../includes/cube3d.h"

void reset_360(float *val)
{
	if (*val < 0)
		*val += (2 * PI);
	if (*val > (2 * PI))
		*val -= (2 * PI);
	return ;
}