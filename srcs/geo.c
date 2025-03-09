#include <miniRT.h>
#include <math.h>

t_vec3	normalize_vec3(t_vec3 vec)
{
	t_vec3	result;
	float	divisor;

	divisor = mag_vec3(vec);
	result = div_vec3(vec, divisor);
	return (result);
}

t_vec3	div_vec3(t_vec3 vec, float d)
{
	t_vec3	result;

	result.x = vec.x / d;
	result.y = vec.y / d;
	result.z = vec.z / d;
	return (result);
}

t_vec3 mult_vec3(t_vec3 vec, float a)
{
	t_vec3	result;

	result.x = vec.x * a;
	result.y = vec.y * a;
	result.z = vec.z * a;
	return (result);
}

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
