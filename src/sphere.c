#include <math.h>
#include "sphere.h"
#include "vector.h"
#include "constants.h"

static int	intersect_sphere(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *out)
{
	// base formula: P = O + tD
	// out->hitPoint = ray.orig + t_hit * ray.dir;
	// In practice, in C this is usually written using vector helper functions.
	// out->hitPoint = vector3_add(ray.orig, vector3_scale(ray.dir, t_hit));
	// or with helper function:
	// out->hitPoint = ray_at(&ray, t_hit); // return O + t*D
	
	const t_sphere	*sphere;
	t_vector3		origin_minus_center; // from sphere center to ray origin
	double			dir_dot_dir;
	double			half_b; // use half of b (b = 2*half_b)
	double			c_term;
	double			disc;
	double			sqrt_disc;
	double			t_hit;
	t_vector3		hit_point;
	t_vector3		hit_normal;
	double			radius;

	if (!obj || !out)
		return (0);
	sphere = (const t_sphere *)obj;
	radius = sphere->diameter * 0.5;
	origin_minus_center = vector3_subtract(ray.orig, sphere->center);
	dir_dot_dir = vector3_dot(ray.dir, ray.dir);
	half_b = vector3_dot(origin_minus_center, ray.dir);
	c_term = vector3_dot(origin_minus_center, origin_minus_center) - radius * radius;
	disc = half_b * half_b - dir_dot_dir * c_term;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	// Try the nearer root first
	t_hit = (-half_b - sqrt_disc) / dir_dot_dir;
	if (t_hit < t_min || t_hit > t_max)
	{
		t_hit = (-half_b + sqrt_disc) / dir_dot_dir;
		if (t_hit < t_min || t_hit > t_max)
			return (0);
	}
	hit_point = ray_at(&ray, t_hit);
	hit_normal = vector3_divide_scalar(vector3_subtract(hit_point, sphere->center), radius);
	// Flip normal to face against the ray for consistent shading
	if (vector3_dot(hit_normal, ray.dir) > 0.0)
		hit_normal = vector3_negate(hit_normal);
	out->t = t_hit;
	out->hitPoint = hit_point;
	out->normal = hit_normal;
	out->material = &obj->material;
	return (1);
}

int	sphere_init(t_sphere *sphere, t_vector3 center, double diameter, t_material material)
{
	if (!sphere || diameter <= 0.0)
		return (1);
	object_init(&sphere->base, SPHERE, material, &intersect_sphere);
	sphere->center = center;
	sphere->diameter = diameter;
	return (0);
}