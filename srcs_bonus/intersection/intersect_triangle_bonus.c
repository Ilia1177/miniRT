#include <minirt_bonus.h>

int intersect_triangle(t_ray *ray, t_object *tr, float *t)
{
    t_vec4 v0 = tr->vertice[0];
    t_vec4 v1 = tr->vertice[1];
    t_vec4 v2 = tr->vertice[2];

    // Calculate triangle edges
    t_vec4 edge1 = sub_vec4(v1, v0);
    t_vec4 edge2 = sub_vec4(v2, v0);

    // Begin Möller-Trumbore algorithm
    t_vec4 h = cross_vec4(ray->d, edge2);
    float det = dot_vec4(edge1, h);

    // If determinant is near zero, ray is parallel to triangle
    if (fabsf(det) < EPSILON)
        return 0;

    float inv_det = 1.0f / det;
    t_vec4 s = sub_vec4(ray->o, v0);
    float u = inv_det * dot_vec4(s, h);

    // Check u bounds
    if (u < 0.0f || u > 1.0f)
        return 0;

    t_vec4 q = cross_vec4(s, edge1);
    float v = inv_det * dot_vec4(ray->d, q);

    // Check v bounds and u+v <= 1
    if (v < 0.0f || (u + v) > 1.0f)
        return 0;

    // Calculate t value
    float t_val = inv_det * dot_vec4(edge2, q);

    // Validate t value
    if (t_val < 0.001f)  // Avoid self-intersection at origin
        return 0;

    *t = t_val;
    return 1;
}
