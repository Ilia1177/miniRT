#include "../../include/matrix.h"

t_mat4	mat_compose(t_mat4 m1, t_mat4 m2)
{
	t_mat4			res;

	res.i = mat_apply(m1, m2.i);
	res.j = mat_apply(m1, m2.j);
	res.k = mat_apply(m1, m2.k);
	res.p = mat_apply(m1, m2.p);
	return (res);
}
