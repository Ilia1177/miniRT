#include "../../include/ft_argb.h"

t_argb	argb_add(t_argb color1, t_argb color2)
{
	t_argb			result;

	result.a = color1.a + color2.a;
	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	argb_clamp(&result);
	return (result);
}
