#include <miniRT_bonus.h>

t_mat4	mat_compose(t_mat4 m1, t_mat4 m2)
{
	t_mat4	res;

	res.i.x = m1.i.x*m2.i.x + m1.j.x*m2.i.y + m1.k.x*m2.i.z + m1.p.x*m2.i.w;
	res.i.y = m1.i.y*m2.i.x + m1.j.y*m2.i.y + m1.k.y*m2.i.z + m1.p.y*m2.i.w;
	res.i.z = m1.i.z*m2.i.x + m1.j.z*m2.i.y + m1.k.z*m2.i.z + m1.p.z*m2.i.w;
	res.i.w = m1.i.w*m2.i.x + m1.j.w*m2.i.y + m1.k.w*m2.i.z + m1.p.w*m2.i.w;
	res.j.x = m1.i.x*m2.j.x + m1.j.x*m2.j.y + m1.k.x*m2.j.z + m1.p.x*m2.j.w;
	res.j.y = m1.i.y*m2.j.x + m1.j.y*m2.j.y + m1.k.y*m2.j.z + m1.p.y*m2.j.w;
	res.j.z = m1.i.z*m2.j.x + m1.j.z*m2.j.y + m1.k.z*m2.j.z + m1.p.z*m2.j.w;
	res.j.w = m1.i.w*m2.j.x + m1.j.w*m2.j.y + m1.k.w*m2.j.z + m1.p.w*m2.j.w;
	res.k.x = m1.i.x*m2.k.x + m1.j.x*m2.k.y + m1.k.x*m2.k.z + m1.p.x*m2.k.w;
	res.k.y = m1.i.y*m2.k.x + m1.j.y*m2.k.y + m1.k.y*m2.k.z + m1.p.y*m2.k.w;
	res.k.z = m1.i.z*m2.k.x + m1.j.z*m2.k.y + m1.k.z*m2.k.z + m1.p.z*m2.k.w;
	res.k.w = m1.i.w*m2.k.x + m1.j.w*m2.k.y + m1.k.w*m2.k.z + m1.p.w*m2.k.w;
	res.p.x = m1.i.x*m2.p.x + m1.j.x*m2.p.y + m1.k.x*m2.p.z + m1.p.x*m2.p.w;
	res.p.y = m1.i.y*m2.p.x + m1.j.y*m2.p.y + m1.k.y*m2.p.z + m1.p.y*m2.p.w;
	res.p.z = m1.i.z*m2.p.x + m1.j.z*m2.p.y + m1.k.z*m2.p.z + m1.p.z*m2.p.w;
	res.p.w = m1.i.w*m2.p.x + m1.j.w*m2.p.y + m1.k.w*m2.p.z + m1.p.w*m2.p.w;
	return (res);
}
