#include <math.h>
#include "cylinder.h"
#include "vector.h"
#include "constants.h"

static int	intersect_cylinder(const t_object *obj,
				t_ray ray, double t_min, double t_max, t_hit *out)
{
    // TODO: implement ray-cylinder intersection
    (void)obj;
	(void)ray;
	(void)t_min;
	(void)t_max;
	(void)out;
	return (1);
}

int	cylinder_init(t_cylinder *cylinder, t_vector3 center, t_vector3 orientation,
			double diameter, double height, t_material material)
{
	if (!cylinder || diameter <= 0.0 || height <= 0.0)
		return (1);
	/* compute normalized axis but also preserve raw orientation */
	if (!vector3_normalize_safe(orientation, &cylinder->axis_unit, RT_EPS))
		return (1);
	object_init(&cylinder->base, CYLINDER, material, &intersect_cylinder);
	cylinder->center = center;
	cylinder->orientation = orientation;
	cylinder->diameter = diameter;
	cylinder->height = height;
	return (0);
}
