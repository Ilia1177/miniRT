/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:58:41 by npolack           #+#    #+#             */
/*   Updated: 2025/04/11 18:53:47 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

// Helper function to check if a wall intersection is within the cylinder's height
static void check_tube(float t, t_vec4 origin, t_vec4 dir, float *t_min)
{
	t_vec4	hit_point;

    if (t > EPSILON)
	{
		hit_point = add_vec4(origin, mult_vec4(dir, t));
        if (hit_point.z >= -0.5f && hit_point.z <= 0.5f) 
            *t_min = fminf(*t_min, t);
    }
}

// Helper function to check intersections with the end caps
static void check_cap(float cap_z, t_vec4 origin, t_vec4 dir, float *t_min)
{
	float	t;
	float	x;
	float	y;

    if (fabsf(dir.z) < EPSILON)
		return;
    t = (cap_z - origin.z) / dir.z;
    if (t > EPSILON)
	{
        x = origin.x + t * dir.x;
        y = origin.y + t * dir.y;
        if (x * x + y * y <= 1.0f)
            *t_min = fminf(*t_min, t);
    }
}

/*******************************************************************************
 * 1. Transform ray to object space
 * 2. Calculate coefficients for the infinite cylinder equation
 * 3. Cylinder is aligned along Z-axis in object space
 * 4. Project direction and origin onto the plane perpendicular to the cylinder's axis
 * 5. Check intersections with the cylinder walls (within height range)
 * 6. Check intersections with the end caps (z=0 and z=height)
 ******************************************************************************/
int intersect_cylinder(t_ray *ray, t_object *cy, float *t)
{
	float			t_min;
	const t_vec4	a = (t_vec4){0, 0, 1, 0};
	const t_vec4	d_pro = sub_vec4(ray->d, mult_vec4(a, dot_vec3(ray->d, a)));
	const t_vec4	o_pro = sub_vec4(ray->o, mult_vec4(a, dot_vec3(ray->o, a)));
	t_quad			equation;

	equation.a = dot_vec3(d_pro, d_pro);
	equation.b = 2 * dot_vec3(d_pro, o_pro);
	equation.c = dot_vec3(o_pro, o_pro) - 1.0f;
	if (!solve_quadratic(&equation))
		return (0);
	t_min = INFINITY;
	check_tube(equation.t[0], ray->o, ray->d, &t_min);
	check_tube(equation.t[1], ray->o, ray->d, &t_min);
	if (!cy->opt)
	{
		check_cap(-0.5f, ray->o, ray->d, &t_min);
		check_cap(0.5f, ray->o, ray->d, &t_min);
	}
	if (t_min < INFINITY)
	{
		*t = t_min;
		return (1);
	}
	return (0);
}
