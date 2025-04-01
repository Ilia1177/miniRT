#include <miniRT.h>
#include <math.h>

float dist_vec3(t_vec3 p1, t_vec3 p2)
{
    return sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
                 (p2.y - p1.y) * (p2.y - p1.y) +
                 (p2.z - p1.z) * (p2.z - p1.z));
}

t_vec3 cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 product;

	product.x = a.y * b.z - a.z * b.y;
	product.y = a.z * b.x - a.x * b.z;
	product.z = a.x * b.y - a.y * b.x;
	product.w = 0;
    return (product);
}

t_vec3	normalize_vec3(t_vec3 vec)
{
	t_vec3	result;
	float	lenght;

	lenght = mag_vec3(vec);
	result = div_vec3(vec, lenght);
	result.w = vec.w;
	return (result);
}

t_vec3	div_vec3(t_vec3 vec, float d)
{
	t_vec3	result;

	result = (t_vec3) {0, 0, 0, 0};
	if (d == 0.0f)
		return (result);
	result.x = vec.x / d;
	result.y = vec.y / d;
	result.z = vec.z / d;
	result.w = vec.w / d;
	return (result);
}

t_vec3	mult_vec3(t_vec3 vec, float a)
{
	t_vec3	result;

	result.x = vec.x * a;
	result.y = vec.y * a;
	result.z = vec.z * a;
	result.w = vec.w * a;
	return (result);
}

float dot_vec3(t_vec3 a, t_vec3 b)
{

	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z; //+ a.w * b.w;
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
	result.w = a.w - b.w;
	return (result);
}

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}
