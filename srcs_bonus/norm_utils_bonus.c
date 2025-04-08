
#include <miniRT_bonus.h>

// same as limit_color(t_argb *color) --> in color.c
void	norm_rgb(t_rgb *c)
{
	c->r = fmin(255, fmax(0, c->r));
	c->g = fmin(255, fmax(0, c->g));
	c->b = fmin(255, fmax(0, c->b));
}

void	norm_float(float *f, float min, float max)
{
	*f = fmin(max, fmax(min, *f));
}

void	norm_int(int *num, int min, int max)
{
	*num = fmin(max, fmax(min, *num));
}
