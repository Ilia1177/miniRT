#include <miniRT_bonus.h>

t_vec4 random_vec4(float magnitude)
{
    // Generate two random numbers in [0, 1)
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;

    // Convert to spherical coordinates
    double theta = 2 * M_PI * u1;         // Azimuthal angle [0, 2π)
    double phi = acos(2 * u2 - 1.0);      // Polar angle [0, π]

    // Compute Cartesian coordinates on the unit sphere
    double sin_phi = sin(phi);
    double x = sin_phi * cos(theta);
    double y = sin_phi * sin(theta);
    double z = cos(phi);

    // Scale to the desired magnitude
    t_vec4 vec;
    vec.x = x * magnitude;
    vec.y = y * magnitude;
    vec.z = z * magnitude;
    return vec;
}
float dist_vec4(t_vec4 p1, t_vec4 p2)
{
	float	dist;

	dist = (p2.x - p1.x) * (p2.x - p1.x) +
		(p2.y - p1.y) * (p2.y - p1.y) +
        (p2.z - p1.z) * (p2.z - p1.z);
    return (sqrtf(dist));
}

t_vec4 cross_vec4(t_vec4 a, t_vec4 b)
{
	t_vec4 product;

	product.x = a.y * b.z - a.z * b.y;
	product.y = a.z * b.x - a.x * b.z;
	product.z = a.x * b.y - a.y * b.x;
	product.w = 0;
    return (product);
}

t_vec4	normalize_vec4(t_vec4 vec)
{
	t_vec4	result;
	float	lenght;

	lenght = mag_vec4(vec);
	result = div_vec4(vec, lenght);
	result.w = 0;
	return (result);
}

t_vec4	div_vec4(t_vec4 vec, float d)
{
	t_vec4	result;

	result = (t_vec4) {0, 0, 0, 0};
	if (d == 0.0f)
		return (result);
	result.x = vec.x / d;
	result.y = vec.y / d;
	result.z = vec.z / d;
	result.w = vec.w;
	return (result);
}

t_vec4	mult_vec4(t_vec4 vec, float a)
{
	t_vec4	result;

	result.x = vec.x * a;
	result.y = vec.y * a;
	result.z = vec.z * a;
	result.w = vec.w;
	return (result);
}

float dot_vec3(t_vec4 a, t_vec4 b)
{

	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

float dot_vec4(t_vec4 a, t_vec4 b)
{

	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (result);
}

float	mag_vec4(t_vec4 a)
{
	float	result;

	result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (result);
}

t_vec4	sub_vec4(t_vec4 a, t_vec4 b)
{
	t_vec4 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

t_vec4	add_vec4(t_vec4 a, t_vec4 b)
{
	t_vec4 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}
