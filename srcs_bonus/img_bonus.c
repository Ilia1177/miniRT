#include <miniRT_bonus.h>

void	rt_put_pixel(const t_img *img, int x, int y, int color)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

//	not in usage for now
uint8_t	rt_get_pixel(t_img img, int x, int y)
{
	uint8_t	p;

	p = *(uint8_t *)((img.addr + (y * img.llen) + (x * img.bpp / 8)));
	return (p);
}

// do not use rgb, but argb instead (color.c) //
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	encode_img_argb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

t_argb	extract_argb(int color)
{
	t_argb	argb_color;

	argb_color.a = (color >> 24) & 0xFF;
	argb_color.r = (color >> 16) & 0xFF;
	argb_color.g = (color >> 8) & 0xFF;
	argb_color.b = color & 0xFF;
	return (argb_color);
}

t_rgb	extract_rgb(int color)
{
	t_rgb	rgb_color;

	rgb_color.r = (color >> 16) & 0xFF;
	rgb_color.g = (color >> 8) & 0xFF;
	rgb_color.b = color & 0xFF;
	return (rgb_color);
}
