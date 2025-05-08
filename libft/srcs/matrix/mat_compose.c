#include "../../include/matrix.h"

t_mat4	mat_compose(t_mat4 m1, t_mat4 m2)
{
	const t_mat4	transposed = mat_transpose(m1);
	t_mat4			res;

	res.i = mat_apply(transposed, m2.i);
	res.j = mat_apply(transposed, m2.j);
	res.k = mat_apply(transposed, m2.k);
	res.p = mat_apply(transposed, m2.p);
	return (res);
}
