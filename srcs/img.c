#include <miniRT.h>

void	rt_put_pixel(t_img *img, t_vec2 pix, int color)
{
	char	*dst;

	dst = img->addr + ((int)pix.y * img->llen + (int)pix.x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	rt_get_pixel(t_img img, int x, int y)
{
	unsigned int	p;

	p = *(unsigned int *)((img.addr + (y * img.llen) + (x * img.bpp / 8)));
	return (p);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

t_rgb	extract_rgb(int color)
{
	t_rgb	rgb_color;

	rgb_color.r = (color >> 16) & 0xFF;
	rgb_color.g = (color >> 8) & 0xFF;
	rgb_color.b = color & 0xFF;
	return (rgb_color);
}

void	norm_rgb(t_rgb *c)
{
	c->r = fmin(255, fmax(0, c->r));
	c->g = fmin(255, fmax(0, c->g));
	c->b = fmin(255, fmax(0, c->b));
}
