#include <minirt_bonus.h>

float	ft_clampf(float f, float min, float max)
{
	float	r_float;

	if (f > max)
		return (max);
	else if (f < min)
		return (min);
	return (f);
}

void	ft_clamp(int *num, int min, int max)
{
	if (*num < min)
		*num = min;
	if (*num > max)
		*num = max;
}
