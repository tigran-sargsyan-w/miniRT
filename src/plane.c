#include <math.h>
#include "plane.h"
#include "vector.h"
#include "constants.h"

static int	intersect_plane(const t_object *obj,
				t_ray ray, double t_min, double t_max, t_hit *out)
{
	// base formula: P = O + tD
	// out->hitPoint = ray.orig + t_hit * ray.dir;
	// In practice, in C this is usually written using vector helper functions.
	// out->hitPoint = vector3_add(ray.orig, vector3_scale(ray.dir, t_hit));
	// or with helper function:
	// out->hitPoint = ray_at(&ray, t_hit); // return O + t*D

	const t_plane *plane;
	double dir_dot_normal;
	double t_hit;
	t_vector3 plane_point_minus_origin;
	t_vector3 hit_point;
	t_vector3 hit_normal;

	if (!obj || !out)
		return (0);
	plane = (const t_plane *)obj;
	dir_dot_normal = vector3_dot(plane->normal_unit, ray.dir);
	// If projection is near zero, ray is parallel to plane
	if (fabs(dir_dot_normal) <= RT_EPS)
		return (0);
	plane_point_minus_origin = vector3_subtract(plane->point, ray.orig);
	t_hit = vector3_dot(plane_point_minus_origin, plane->normal_unit) / dir_dot_normal;
	if (t_hit < t_min || t_hit > t_max)
		return (0);
	hit_point = ray_at(&ray, t_hit);
	hit_normal = plane->normal_unit;
	// Ensure normal faces against the ray direction (for consistent shading)
	if (vector3_dot(hit_normal, ray.dir) > 0.0)
		hit_normal = vector3_negate(hit_normal);
	out->t = t_hit;
	out->hitPoint = hit_point;
	out->normal = hit_normal;
	out->material = &obj->material;
	out->object = obj;
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
