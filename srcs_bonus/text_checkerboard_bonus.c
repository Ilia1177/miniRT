#include <miniRT.h>

t_argb	invert_color(t_argb color)
{
	t_argb new_color;

	new_color.a = 255 - color.a;
	new_color.r = 255 - color.r;
	new_color.g = 255 - color.g;
	new_color.b = 255 - color.b;
	return (new_color);
}

t_argb	checkerboard_plane(t_vec3 hit_point, t_object *obj)
{
	int		x;
	int		y;
	int		z;
	t_argb	color;

	x = floor(hit_point.x * CBOARD_SCALE);
	z = floor(hit_point.z * CBOARD_SCALE);
	if (fabs(obj->axis.y)> 0.9f)
		y = z;
	else
		y = floor(hit_point.y * CBOARD_SCALE) + z;
	if ((x + y) % 2 == 0)
		color = invert_color(obj->color);
	else
		color = obj->color;
	return (color);
}

t_board	checkerboard(t_argb color1, t_argb color2)
{
	t_board	tab;
	int		i;
	int		j;

	j = 0;
	while (j < CBOARD_H)
	{
		i = 0;
		while (i < CBOARD_W)
		{
			if ((i + j) % 2 == 0)
				tab.color[j][i] = color1;
			else
				tab.color[j][i] = color2;
			i++;
		}
		j++;
	}
	return (tab);
}

t_argb	checkerboard_at(float u, float v, t_argb obj_color)
{
	t_argb	color;
	const t_board	tab = checkerboard(obj_color, invert_color(obj_color));
	int		u2;
	int		v2;

	v2 = fmin(floor(v * CBOARD_H), CBOARD_H - 1);
	//printf("v = %d\t", v);
	//u = round(x);
	u2 = fmin(floor(u * CBOARD_W), CBOARD_H - 1);
	//printf("u = %d\n", u);
	//tab = checkerboard(obj_color, CBOARD_COLOR);
	color = tab.color[v2][u2];
	return (color);
}

t_uv	sphere_map(t_vec3 point, float radius)
{
	t_uv		uv;
	/* const float	theta = atan2(point.x, point.z); */
	/* const float	radius = mag_vec3(point); */
	/* const float	phi = acos(point.y / radius); */
	/* const float	raw_u = theta / (2 * M_PI); */
	/**/
	/* uv.u = 1 - (raw_u + 0.5); */
	/* uv.u = ABS(uv.u); */
	/* uv.v = 1 - phi / M_PI; */
	/* uv.v = ABS(uv.v); */
	const float	theta = atan2(point.z, point.x);
	//const float	radius = mag_vec3(point);
	const float	phi = asin(point.y / radius);
	const float	raw_u = theta / (2 * M_PI);

	uv.u = raw_u + 0.5f;
	uv.u = fabs(uv.u);
	uv.v = 0.5f - phi / M_PI;
	uv.v = fabs(uv.v);
	return (uv);
}

t_uv cylinder_maplast(t_vec3 point, t_vec3 axis, float radius, float height)
{
    t_uv uv;
    float scale;

    scale = 0.1f;
    
    // 1. Projection verticale (V)
    float h = dot_vec3(point, axis); // Position le long de l'axe
    uv.v = fmodf(fabs(h / height * scale*4.0f), 1.0f);

    // 2. Projection horizontale (U) - version corrigée
    t_vec3 radial = sub_vec3(point, mult_vec3(axis, h));
    float theta = atan2(radial.z, radial.x);
    
    // Compensation de la courbure
    uv.u = fmodf(fabs(theta * radius * scale / (2.0f * M_PI)), 1.0f);

    return uv;
}
/*****************************************************************************
 	* hp = hit point
******************************************************************************/
t_argb	pattern_color(t_ray *ray, t_object *obj, t_data *scene)
{
	t_uv	uv;
	t_argb	color;
	t_vec3	hp;

	hp = mat_apply(obj->i_m, ray->o);
	(void)scene;
	if (obj->type == SPHERE && obj->pattern)
	{
		hp = sub_vec3(hp, obj->pos);
		uv = sphere_map(hp, obj->radius);
		//color = checkerboard_at(uv.u, uv.v, obj->color);
		color = text_img_at(uv.u, uv.v, obj->img);
		//printf("color [%.2f] [%.2f]\n", uv.u, uv.v);
	}
	else if (obj->type == PLANE && obj->pattern)
	{
		color = checkerboard_plane(hp, obj);
	    //printf("color [%.2f] [%.2f]\n", uv.u, uv.v);
	}
	else if (obj->type == CYLINDER && obj->pattern)
	{
		//hp = sub_vec3(hp, obj->pos);
		uv = cylinder_maplast(hp, normalize_vec3(obj->axis), obj->radius, obj->height);
		color = checkerboard_at(uv.u, uv.v, obj->color);
		//printf("color [%.2f] [%.2f]\n", uv.u, uv.v);
	}
	else
		color = obj->color;
	return (color);
}

