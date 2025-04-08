#include <miniRT_bonus.h>

t_img	*text_img(t_data *scene, char *path)
{
	t_img		*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(scene->mlx, path, &img->w, &img->h);
	if (img->ptr)
		img->addr = mlx_get_data_addr(img->ptr,
			&img->bpp, &img->llen, &img->endian);
	return (img);
}

t_argb	text_img_at(float u, float v, t_img *img)
{
	t_argb		color;
	t_uv		uv2;
	//const t_img	img = text_img(scene);

	uv2.u = fmin(floor(u * img->w), img->w);
	uv2.v = fmin(floor(v * img->h), img->h);
	uv2.u = uv2.u + floor(img->w / 4);
	color = extract_argb(rt_get_pixel(*img, uv2.u, uv2.v));
	return (color);
}
