#include <miniRT.h>

//	int	rt_sphere(int x, int y, int z, int diametre)
//	{
//		
//	}
//	

double	dist(t_vec2 a, t_vec2 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

t_vec2	sub_vec(t_vec2 a, t_vec2 b)
{
	t_vec2 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_vec2	add_vec(t_vec2 a, t_vec2 b)
{
	t_vec2 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}


int	rt_circle(t_circle circle, t_img *img)
{
	t_vec2	pos; //to be renamed pix

	pos.y = circle.pos.y - circle.radius;
	if (pos.y < 0)
		pos.y = 0;
	while (pos.y < HEIGHT)
	{
		pos.x = circle.pos.x - circle.radius;
		if (pos.x < 0)
			pos.x = 0;
		while (pos.x < WIDTH)
		{
			
			if (dist(pos, circle.pos) <= circle.radius)
				rt_put_pixel(img, pos.x, pos.y, 0x00FF0000);
			pos.x++;
		}
		pos.y++;
	}
	return (0);
}

int	rt_rect(t_rect rect, t_img *img)
{
	t_vec2	pix;

	pix.y = 0;
	while (pix.y < HEIGHT)
	{
		pix.x = 0;
		while (pix.x < WIDTH)
		{
			if (pix.x > rect.pos.x - rect.size.x / 2 && pix.x < rect.pos.x + rect.size.y / 2)  
				if (pix.y > rect.pos.y - rect.size.y / 2 && pix.y < rect.pos.y + rect.size.y / 2)  
					rt_put_pixel(img, pix.x, pix.y, 0x00FF0000);
			pix.x++;
}
		pix.y++;
	}
	return (0);
}

int	rt_ray(t_ray ray, t_circle object, t_img *img)
{
	t_vec2 pix;

	int end_of_screen = 0;
	int	object_hit = 0;

	float step = ray.thickness;
	pix = ray.origin;
	while (!end_of_screen && !object_hit)
	{
		pix.x += step * cos(ray.angle);
		pix.y += step * sin(ray.angle);
		rt_put_pixel(img, pix.x, pix.y, 0xFFFFFFFF);
		if (pix.x < 0 || pix.x > WIDTH)
			end_of_screen = 1;
		if (pix.y < 0 || pix.y > HEIGHT)
			end_of_screen = 1;
		if (dist(pix, object.pos) < object.radius)
			object_hit = 1;

	}
	return (0);
}


int point_is_on_line(t_vec2 a, t_vec2 b, t_vec2 c) {
    double cross_product = (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);

	printf("point is on line'n\n");
    // If cross-product is zero, points are collinear (on the same line)
    if (cross_product > -1 && cross_product < 1)
        return 1;  // True: C is on the line
    return 0;      // False: C is not on the line
}

/******** Bresenham’s Line Algorithm */
void draw_line(int x1, int y1, int x2, int y2, t_img *img) 
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
	{
        rt_put_pixel(img, x1, y1, 0x00FF0000);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
		if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


