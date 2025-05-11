
#include <minirt_bonus.h>

	// Discard rays outside circular fisheye bounds
t_vec4 fisheye_proj(t_vec2 cnv, float fov_degrees)
{
	t_vec4 ray;
	float  x = (((float)cnv.x + WIDTH / 2) / WIDTH * 2.0f) - 1.0f;
	float  y = (((float)cnv.y + HEIGHT / 2) / HEIGHT * 2.0f) - 1.0f;
	float r = sqrtf(x * x + y * y);
	float max_fov_rad = fov_degrees * (M_PI / 180.0f) / 2.0f;

	if (r > 1.0f) {
		ray.x = ray.y = ray.z = ray.w = 0.0f;
		return ray;
	}

	// Angle from center
	float theta = r * max_fov_rad;

	// Angle of the point in the image plane
	float phi = atan2f(y, x);

	// Spherical to Cartesian
	ray.x = sinf(theta) * cosf(phi);
	ray.y = sinf(theta) * sinf(phi);
	ray.z = cosf(theta);
	ray.w = 0.0f;
    return ray;
}

t_vec4  stereographic_proj(t_vec2 cnv, t_viewport vp)
{
	(void)vp;
	t_vec4      dir;
	const float phi = (((float)cnv.x + WIDTH / 2) / WIDTH) * 2 * M_PI;
	const float theta = (((float)cnv.y + HEIGHT / 2) / HEIGHT) * M_PI;

	dir.x = sinf(theta) * cosf(phi);
	dir.y = cosf(theta);
	dir.z = sinf(theta) * sinf(phi);
	return (dir);
}

t_vec4  equirectangular_proj(t_vec2 cnv, t_viewport vp)
{
    (void)vp;
    t_vec4      dir;
    const float phi = (((float)cnv.x + (float)WIDTH / 2) / (float)WIDTH) * 2 * M_PI;
    const float theta = (1.0f - ((float)cnv.y + (float)HEIGHT / 2) / (float)HEIGHT) * M_PI;

	dir.x = sin(theta) * cos(phi);
	dir.y = cos(theta);
	dir.z = sin(theta) * sin(phi);
    return (dir);
}

// get location of the point in the viemport from canvas'location
t_vec4	pinhole_proj(t_vec2 cnv, t_viewport vp)
{
	t_vec4	dir;

	dir.x = (float)cnv.x * vp.w / WIDTH;
	dir.y = (float)cnv.y * vp.h / HEIGHT;
	dir.z = vp.pos.z;
	dir.w = 0.0f;
	dir = normalize_vec4(dir);
	return (dir);
}
t_vec4	projection(t_vec2 cnv, t_data *scene)
{
	t_vec4	dir;

    if (scene->viewport.proj == STEREO)
		dir = stereographic_proj(cnv, scene->viewport);
	else if (scene->viewport.proj == EQUIRECT)
		dir = equirectangular_proj(cnv, scene->viewport);
	else if (scene->viewport.proj == FISHEYE)
		dir = fisheye_proj(cnv, scene->cam.fov);
	else 
		dir = pinhole_proj(cnv, scene->viewport);
	return (dir);

}
