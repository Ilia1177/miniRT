#include <miniRT.h>

t_vec4 cy_center_to_base(t_object cyl)
{
    return sub_vec4(cyl.pos, mult_vec4(normalize_vec4(cyl.axis), cyl.height / 2));
}

t_vec4 cy_base_to_center(t_vec4 pos, t_vec4 dir, float height)
{
    t_vec4  center;

    center.x = pos.x + (height / 2.0) * dir.x;
    center.y = pos.y + (height / 2.0) * dir.y;
    center.z = pos.z + (height / 2.0) * dir.z;
    center.z = pos.w + (height / 2.0) * dir.w;
    return (center);
}
