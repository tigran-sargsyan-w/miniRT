#include <math.h>
#include "plane.h"
#include "vector.h"
#include "constants.h"

static int	intersect_plane(const t_object *obj,
				t_ray ray, double t_min, double t_max, t_hit *out)
{
    // TODO: implement ray-plane intersection
    (void)obj;
	(void)ray;
	(void)t_min;
	(void)t_max;
	(void)out;
	return (1);
}

int	plane_init(t_plane *plane, t_vector3 point, t_vector3 normal, t_material material)
{
	if (!plane)
		return (1);
	// compute normalized unit normal but preserve raw normal
	if (!vector3_normalize_safe(normal, &plane->normal_unit, RT_EPS))
		return (1);
	object_init(&plane->base, PLANE, material, &intersect_plane);
	plane->point = point;
	plane->normal = normal;
	return (0);
}
