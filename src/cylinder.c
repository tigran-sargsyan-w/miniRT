#include <math.h>
#include "cylinder.h"
#include "vector.h"
#include "constants.h"

static int	intersect_cylinder(const t_object *obj,
				t_ray ray, double t_min, double t_max, t_hit *out)
{
	// Finite right circular cylinder with axis "axis_unit",
	// center at "center" (we'll consider axis passing through center),
	// radius = diameter/2, finite height along axis direction.
	// Algorithm:
	// 1) Project ray direction and origin-to-center onto plane orthogonal to axis
	// 2) Solve quadratic for infinite cylinder (|w| = radius) where w is component perpendicular to axis
	// 3) Check t roots within [t_min, t_max] and within finite height bounds via projection onto axis
	const t_cylinder *cyl;
	t_vector3  axis;      // unit axis direction
	t_vector3  origin_to_center; // ray.orig - cyl.center
	double     radius;

	double dir_dot_axis; // ray.dir · axis
	double oc_dot_axis;  // (origin_to_center) · axis
	t_vector3 dir_perp_axis; // component of ray.dir perpendicular to axis
	t_vector3 oc_perp_axis;  // component of origin_to_center perpendicular to axis

	double quad_a, quad_b, quad_c; // quadratic coefficients for infinite cylinder
	double disc, sqrt_disc;
	double t_candidates[2];
	int    i;

	if (!obj || !out)
		return (0);
	cyl = (const t_cylinder *)obj;
	axis = cyl->axis_unit;
	origin_to_center = vector3_subtract(ray.orig, cyl->center);
	radius = cyl->diameter * 0.5;

	dir_dot_axis = vector3_dot(ray.dir, axis);
	oc_dot_axis = vector3_dot(origin_to_center, axis);
	// perpendicular components
	dir_perp_axis = vector3_subtract(ray.dir,         vector3_scale(axis, dir_dot_axis));
	oc_perp_axis  = vector3_subtract(origin_to_center, vector3_scale(axis, oc_dot_axis));

	quad_a = vector3_dot(dir_perp_axis, dir_perp_axis);
	quad_b = 2.0 * vector3_dot(dir_perp_axis, oc_perp_axis);
	quad_c = vector3_dot(oc_perp_axis, oc_perp_axis) - radius * radius;

	// If quad_a is near zero, ray is parallel to axis; treat as no side hit
	if (fabs(quad_a) <= RT_EPS)
		return (0);

	disc = quad_b * quad_b - 4.0 * quad_a * quad_c;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);

	t_candidates[0] = (-quad_b - sqrt_disc) / (2.0 * quad_a);
	t_candidates[1] = (-quad_b + sqrt_disc) / (2.0 * quad_a);

	for (i = 0; i < 2; ++i)
	{
		double t_hit = t_candidates[i];
		if (t_hit < t_min || t_hit > t_max)
			continue;
		// Check finite height: distance along axis from center must be within [-h/2, h/2]
		t_vector3 hit_point = ray_at(&ray, t_hit);
		t_vector3 center_to_point = vector3_subtract(hit_point, cyl->center);
		double axis_proj = vector3_dot(center_to_point, axis);
		if (fabs(axis_proj) > (cyl->height * 0.5 + RT_EPS))
			continue;
		// Compute normal: component of (hit_point - center) perpendicular to axis, normalized
		t_vector3 radial_component = vector3_subtract(center_to_point, vector3_scale(axis, axis_proj));
		t_vector3 hit_normal;
		if (!vector3_normalize_safe(radial_component, &hit_normal, RT_EPS))
			continue;
		if (vector3_dot(hit_normal, ray.dir) > 0.0)
			hit_normal = vector3_negate(hit_normal);
		out->t = t_hit;
		out->hitPoint = hit_point;
		out->normal = hit_normal;
		out->material = &obj->material;
		return (1);
	}
	return (0);
}

int	cylinder_init(t_cylinder *cylinder, t_vector3 center, t_vector3 orientation,
			double diameter, double height, t_material material)
{
	if (!cylinder || diameter <= 0.0 || height <= 0.0)
		return (1);
	// compute normalized axis but also preserve raw orientation
	if (!vector3_normalize_safe(orientation, &cylinder->axis_unit, RT_EPS))
		return (1);
	object_init(&cylinder->base, CYLINDER, material, &intersect_cylinder);
	cylinder->center = center;
	cylinder->orientation = orientation;
	cylinder->diameter = diameter;
	cylinder->height = height;
	return (0);
}
