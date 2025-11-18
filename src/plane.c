#include <math.h>
#include "plane.h"
#include "vector.h"
#include "constants.h"
#include "transform.h"
#include "object.h"

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

static void plane_translate(t_object *obj, t_vector3 delta)
{
	t_plane *pl = (t_plane*)obj;
	pl->point = vector3_add(pl->point, delta);
}

static void plane_rotate(t_object *obj, double rx, double ry, double rz)
{
	t_plane *pl = (t_plane*)obj;
	t_vector3 n = rotate_euler_vec(pl->normal, rx, ry, rz);
	pl->normal = n;
	if (!vector3_normalize_safe(pl->normal, &pl->normal_unit, RT_EPS))
		pl->normal_unit = VECTOR3_UNIT_Y;
}

static void plane_scale_uniform(t_object *obj, double factor)
{
	(void)obj; (void)factor; // no-op for plane
}

static void plane_scale_height(t_object *obj, double factor)
{
	(void)obj; (void)factor; // no-op for plane
}

int	plane_init(t_plane *plane, t_vector3 point, t_vector3 normal, t_material material)
{
	if (!plane)
		return (1);
	// compute normalized unit normal but preserve raw normal
	if (!vector3_normalize_safe(normal, &plane->normal_unit, RT_EPS))
		return (1);
	object_init(&plane->base, PLANE, material, &intersect_plane,
		&plane_translate, &plane_rotate, &plane_scale_uniform, &plane_scale_height);
	plane->point = point;
	plane->normal = normal;
	return (0);
}
