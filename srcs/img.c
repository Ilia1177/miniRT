#include <miniRT.h>

void	rt_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	rt_get_pixel(t_img img, int x, int y)
{
	unsigned int	p;

	p = *(unsigned int *)((img.addr + (y * img.llen) + (x * img.bpp / 8)));
	return (p);
}


