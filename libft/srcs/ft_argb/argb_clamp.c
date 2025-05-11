#include "../../include/ft_argb.h"

static int	clamp(int value, int min, int max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

void	argb_clamp(t_argb *color)
{
	color->a = clamp(color->a, 0, 255);
	color->r = clamp(color->r, 0, 255);
	color->g = clamp(color->g, 0, 255);
	color->b = clamp(color->b, 0, 255);
}
