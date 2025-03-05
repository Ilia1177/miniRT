//RAY TRACING


// Screen to Viewport
 S.x = C.w / 2 + C.x
 S.y = C.h / 2 - C.y


// Canvas to ViewPort
 V.x = C.x * (V.w / C.w)
 V.y = C.y * (V.h / C.h)


// Point P on the ray
  P = O + t ( V − O )

// Sphere:
 ⟨ P − C , P − C ⟩ = r^2

// Intersection Ray / Sphere (quadratic equation)
t1, t2 = (−b ± sqrt(b^2 − 4 * a * c )) / 2 * a 


t_vec2 cnv_to_screen(t_vec2 cnv)
{
	t_vec2 screen;

	screen.x = (cnv.x / 2) + cnv.x;
	screen.y = (cnv.h / 2) - cnv.y;
	return (screen);
}

void	display_color(cam, cnv)
{
	t_vec2	pix;
	t_vec3	vp;

	pix.x = -cnv.w / 2;
	while (pix.x < cnv.w / 2)
	{
		pix.y = -cnv.h / 2;
		while (pix.y < cnv.h / 2)
		{
			vp = cnv_to_vp(pix);
			color = throw_ray(cam, vp, 1, INT_MAX);
			pix = cnv_to_screen(pix);
			rt_put_pixel(img, pix, color);
		}
	}
}


t_vec3 cnv_to_vp(x, y)
{
	t_vec3 view_port;

	view_port.x = x * (Vw / Cw);
	view_port.y = y * (Vh / Ch);
	view_port.z = 1;
	return (view_port);
}

int	throw_ray(t_vec3 cam, t_vec3 dir, t_min, t_max, t_data *scene)
{
	int			closest_t;
	t_sphere	*closest_sphere;
	t_sphere	*curr_sphere;
	float	solution[2];

	closest_t = INT_MAX;
	closest_sphere = NULL;
	curr_sphere = scene->sphere;
	while (curr_sphere)
	{
		solution = IntersectRaySphere(cam, dir, curr_sphere);
		if (solution[0] >= t_min && solution[0] <= t_max)
		{
			if (solution[0] < closest_t)
			{
				closest_t = solution[0];
				closest_sphere = curr_sphere;
			}
		}
		if (solution[1] >= t_min && solution[1] <= t_max)
		{
			if (solution[1] < closest_t)
			{
				closest_t = solution[1];
				closest_sphere = curr_sphere;
			}
		}
	curr_sphere = curr_sphere->next;
	}
	if (closest_sphere == NULL)
		return (0x00000000);
	return (closest_sphere.color);


//        for sphere in scene.spheres {
//            t1, t2 = IntersectRaySphere(O, D, sphere)
//            if t1 in [t_min, t_max] and t1 < closest_t {
//                closest_t = t1
//                closest_sphere = sphere
//            }
//            if t2 in [t_min, t_max] and t2 < closest_t {
//                closest_t = t2
//                closest_sphere = sphere
//            }
//        }
//        if closest_sphere == NULL {
//           ❶return BACKGROUND_COLOR
//        }
//        return closest_sphere.color
    }

float *IntersectRaySphere(t_vec3 cam, dir, t_sphere sphere)
{
	float r = sphere.radius
	float result[2];

	float	r = sphere.radius;
	float	a, b, c;
	float	discriminant;
	float	substract;
       //CO = O - sphere.center
	substract = sub_vec3(cam, sphere.center);

        a = dot_product(dir, dir);
        b = 2 * dot_product(substrac, dir);
        c = dot_product(substrac, substract) - r * r;

        discriminant = b * b - 4 * a * c
        if (discriminant < 0)
		{
			result[0] = INT_MAX;
			result[1] = INT_MIN;
            return (result);
        }
        result[0] = (-b + sqrt(discriminant)) / (2*a)
        result[1] = (-b - sqrt(discriminant)) / (2*a)
        return (result);
    }
