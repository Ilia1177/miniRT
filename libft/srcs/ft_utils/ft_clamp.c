#include "../../include/libft.h"

float	ft_clampf(float f, float min, float max)
{
	if (f > max)
		return (max);
	else if (f < min)
		return (min);
	return (f);
}

int	ft_clamp(int num, int min, int max)
{
	if (num > max)
		return (max);
	else if (num < min)
		return (min);
	return (num);
}
