#include <miniRT.h>

t_vec3 cy_center_to_base(t_object cyl)
{
    return sub_vec3(cyl.pos, mult_vec3(normalize_vec3(cyl.axis), cyl.height / 2));
}

/* t_vec3  cy_center_to_base(t_object cy) */
/* { */
/*     t_vec3 base_cy_pos; */
/*    */
/*     base_cy_pos.x = cy.pos.x - (cy.height / 2.0) * cy.dir.x; */
/*     base_cy_pos.y = cy.pos.y - (cy.height / 2.0) * cy.dir.y; */
/*     base_cy_pos.z = cy.pos.z - (cy.height / 2.0) * cy.dir.z; */
/*     base_cy_pos.w = cy.pos.w - (cy.height / 2.0) * cy.dir.w; */
/*     return (base_cy_pos); */
/* } */

t_vec3 cy_base_to_center(t_vec3 pos, t_vec3 dir, float height)
{
    t_vec3  center;

    center.x = pos.x + (height / 2.0) * dir.x;
    center.y = pos.y + (height / 2.0) * dir.y;
    center.z = pos.z + (height / 2.0) * dir.z;
    center.z = pos.w + (height / 2.0) * dir.w;
    return (center);
}
