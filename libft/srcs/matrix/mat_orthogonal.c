#include "../../include/matrix.h"
#include "../../include/ft_printf.h"	//suppr

t_mat4	mat_orthogonal(t_vec4 forward)
{
	t_mat4			orthogonal;
	const t_vec4	up = {0, 1, 0, 0}; // World up
	t_vec4			right;
	t_vec4			new_up;

	forward = normalize_vec4(forward);
	right = normalize_vec4(cross_vec4(up, forward));
	// If forward is parallel to up, create a fallback right vector
	if (mag_vec4(right) < EPSILON)
	{
		right = (t_vec4){1, 0, 0, 0};
		ft_printf("right:1, 0, 0\n");
	}
//	if (mag_vec4(right) < EPSILON)
//		right = normalize_vec4(cross_vec4(forward, (t_vec4){1, 0, 0, 0}));

	new_up = normalize_vec4(cross_vec4(forward, right));
	// Compose the camera matrix
	orthogonal = mat_init_id();
	orthogonal.i = right;
	orthogonal.j = new_up;
	orthogonal.k = forward;
	orthogonal.p = (t_vec4) {0, 0, 0, 1}; // Preserve position

	return (orthogonal);
}

t_mat4	mat_orthogonal2(t_vec4 dir)
{
	t_mat4			orthogonal;
	float			dir_dot_up;
	const float		mag = mag_vec4(dir);
	const t_vec4	up = {0, 1, 0, 0};
	const t_vec4	normalized_dir = normalize_vec4(dir);

	orthogonal = mat_init_id();
	if (mag < EPSILON)
		return (orthogonal);
	orthogonal.k = normalized_dir;
	dir_dot_up = dot_vec3(normalized_dir, up);
	if (fabsf(dir_dot_up) >= 1.0f - EPSILON)
	{
		orthogonal.i = normalize_vec4(cross_vec4((t_vec4){1, 0, 0, 0}, normalized_dir));
		//ft_printf("switch vector base\n");
	//	return (orthogonal);
	}
	else
	{
		orthogonal.i = cross_vec4(up, normalized_dir);
		ft_printf("up = 0, 1, 0\n");
		
	}
	orthogonal.i = normalize_vec4(orthogonal.i);
	orthogonal.j = cross_vec4(orthogonal.k, orthogonal.i);
	orthogonal.p = (t_vec4){0, 0, 0, 1};
	return (orthogonal);
}
