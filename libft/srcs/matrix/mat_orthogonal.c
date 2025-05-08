#include "../../include/matrix.h"

t_mat4	mat_orthogonal(t_vec4 dir)
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
		orthogonal.i = cross_vec4((t_vec4){1, 0, 0, 0}, normalized_dir);
	else
		orthogonal.i = cross_vec4(up, normalized_dir);
	orthogonal.i = normalize_vec4(orthogonal.i);
	orthogonal.j = cross_vec4(orthogonal.k, orthogonal.i);
	orthogonal.p = (t_vec4){0, 0, 0, 1};
	return (orthogonal);
}
