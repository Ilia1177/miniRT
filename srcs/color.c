#include <miniRT.h>

void	limit_color(t_argb *color)
{
	color->a = fmin(255, fmax(0, color->a));
	color->r = fmin(255, fmax(0, color->r));
	color->g = fmin(255, fmax(0, color->g));
	color->b = fmin(255, fmax(0, color->b));
}

unsigned int encode_argb(t_argb color)
{
	const uint8_t alpha = color.a;
   	const uint8_t red = color.r;
   	const uint8_t green = color.g;
	const uint8_t blue = color.b;

	return (alpha << 24 | red << 16 | green << 8 | blue);
}

t_argb	ease_color(t_argb color, uint8_t ease)
{
	t_argb	result;
	
	result.a = ease - color.a;
	result.r = ease - color.r;
	result.g = ease - color.g;
	result.b = ease - color.b;
	limit_color(&result);
	return (color);
}

t_argb	mult_colors(t_argb color1, t_argb color2)
{
	t_argb	result;

	result.a = color1.a * (color2.a / 255.0);
	result.r = color1.r * (color2.r / 255.0);
	result.g = color1.g * (color2.g / 255.0);
	result.b = color1.b * (color2.b / 255.0);
	limit_color(&result);
	return (result);
}

t_argb	add_colors(t_argb color1, t_argb color2)
{
	t_argb			result;

	result.a = color1.a + color2.a;
	result.r = color1.r + color2.r;
	result.b = color1.b + color2.b;
	result.g = color1.g + color2.g;
	limit_color(&result);
	return (result);
}
