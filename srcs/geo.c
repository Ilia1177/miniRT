#include <miniRT.h>
#include <math.h>

float dot_product(t_vec3 a, t_vec3 b)
{

	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

float	mag_vec3(t_vec3 a)
{
	float	result;

	result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (result);
}

double	dist(t_vec2 a, t_vec2 b)
{
	double dist;

	dist = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	return (dist);
}

t_vec3	sub_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
