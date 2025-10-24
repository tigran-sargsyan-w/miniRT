#include <math.h>
#include "sphere.h"
#include "vector.h"
#include "constants.h"

static int	intersect_sphere(const t_object *obj,
					t_ray ray, double t_min, double t_max, t_hit *out)
{
    // TODO: implement ray-sphere intersection
	(void)obj;
	(void)ray;
	(void)t_min;
	(void)t_max;
	(void)out;
	return (1);
}

int	sphere_init(t_sphere *sphere, t_vector3 center, double radius, t_material material)
{
	if (!sphere || radius <= 0.0)
		return (1);
	object_init(&sphere->base, OBJ_SPHERE, material, &intersect_sphere);
	sphere->center = center;
	sphere->radius = radius;
	return (0);
}