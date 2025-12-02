#include <math.h>
#include "cylinder.h"
#include "vector.h"
#include "constants.h"
#include <stdio.h>
#include "transform.h"
#include "object.h"

static int	intersect_cylinder(const t_object *obj,
				t_ray ray, double t_min, double t_max, t_hit *out)
{
	// base formula: P = O + tD
	// out->hitPoint = ray.orig + t_hit * ray.dir;
	// In practice, in C this is usually written using vector helper functions.
	// out->hitPoint = vector3_add(ray.orig, vector3_scale(ray.dir, t_hit));
	// or with helper function:
	// out->hitPoint = ray_at(&ray, t_hit); // return O + t*D
	
	// Finite right circular cylinder with caps.
	const t_cylinder *cyl;
	t_vector3  axis;                // unit axis direction
	t_vector3  origin_to_center;    // ray.orig - cyl.center
	double     radius;

	double dir_dot_axis; // ray.dir · axis
	double oc_dot_axis;  // (origin_to_center) · axis
	t_vector3 dir_perp_axis; // component of ray.dir perpendicular to axis
	t_vector3 oc_perp_axis;  // component of origin_to_center perpendicular to axis

	double quad_a, quad_b, quad_c; // quadratic coefficients for side (infinite cylinder)
	double disc, sqrt_disc;
	double side_t1, side_t2;

	int     has_hit;
	double  best_t;
	t_hit   best_hit;

	if (!obj || !out)
		return (0);
	cyl = (const t_cylinder *)obj;
	axis = cyl->axis_unit;
	origin_to_center = vector3_subtract(ray.orig, cyl->center);
	radius = cyl->diameter * 0.5;

	has_hit = 0;
	best_t = t_max;

	// --- Side intersection (infinite cylinder reduced by height) ---
	dir_dot_axis = vector3_dot(ray.dir, axis);
	oc_dot_axis = vector3_dot(origin_to_center, axis);
	// perpendicular components
	dir_perp_axis = vector3_subtract(ray.dir,         vector3_scale(axis, dir_dot_axis));
	oc_perp_axis  = vector3_subtract(origin_to_center, vector3_scale(axis, oc_dot_axis));

	quad_a = vector3_dot(dir_perp_axis, dir_perp_axis);
	quad_b = 2.0 * vector3_dot(dir_perp_axis, oc_perp_axis);
	quad_c = vector3_dot(oc_perp_axis, oc_perp_axis) - radius * radius;

	if (fabs(quad_a) > RT_EPS)
	{
		disc = quad_b * quad_b - 4.0 * quad_a * quad_c;
		if (disc >= 0.0)
		{
			sqrt_disc = sqrt(disc);
			side_t1 = (-quad_b - sqrt_disc) / (2.0 * quad_a);
			side_t2 = (-quad_b + sqrt_disc) / (2.0 * quad_a);

			// check first root
			if (side_t1 >= t_min && side_t1 <= t_max)
			{
				t_vector3 hit_point = ray_at(&ray, side_t1);
				t_vector3 center_to_point = vector3_subtract(hit_point, cyl->center);
				double axis_proj = vector3_dot(center_to_point, axis);
				if (fabs(axis_proj) <= (cyl->height * 0.5 + RT_EPS))
				{
					t_vector3 radial_component = vector3_subtract(center_to_point, vector3_scale(axis, axis_proj));
					t_vector3 hit_normal;
					if (vector3_normalize_safe(radial_component, &hit_normal, RT_EPS))
					{
						if (vector3_dot(hit_normal, ray.dir) > 0.0)
							hit_normal = vector3_negate(hit_normal);
						if (!has_hit || side_t1 < best_t)
						{
							has_hit = 1;
							best_t = side_t1;
							best_hit.t = side_t1;
							best_hit.hitPoint = hit_point;
							best_hit.normal = hit_normal;
							best_hit.material = &obj->material;
						}
					}
				}
			}

			// check second root
			if (side_t2 >= t_min && side_t2 <= t_max)
			{
				t_vector3 hit_point = ray_at(&ray, side_t2);
				t_vector3 center_to_point = vector3_subtract(hit_point, cyl->center);
				double axis_proj = vector3_dot(center_to_point, axis);
				if (fabs(axis_proj) <= (cyl->height * 0.5 + RT_EPS))
				{
					t_vector3 radial_component = vector3_subtract(center_to_point, vector3_scale(axis, axis_proj));
					t_vector3 hit_normal;
					if (vector3_normalize_safe(radial_component, &hit_normal, RT_EPS))
					{
						if (vector3_dot(hit_normal, ray.dir) > 0.0)
							hit_normal = vector3_negate(hit_normal);
						if (!has_hit || side_t2 < best_t)
						{
							has_hit = 1;
							best_t = side_t2;
							best_hit.t = side_t2;
							best_hit.hitPoint = hit_point;
							best_hit.normal = hit_normal;
							best_hit.material = &obj->material;
						}
					}
				}
			}
		}
	}

	// --- Caps intersection (top and bottom disks) ---
	{
		double denom = vector3_dot(ray.dir, axis);
		if (fabs(denom) > RT_EPS)
		{
			t_vector3 top_center = vector3_add(cyl->center, vector3_scale(axis, cyl->height * 0.5));
			t_vector3 bottom_center = vector3_subtract(cyl->center, vector3_scale(axis, cyl->height * 0.5));

			// Top cap
			{
				double t_cap = vector3_dot(vector3_subtract(top_center, ray.orig), axis) / denom;
				if (t_cap >= t_min && t_cap <= t_max)
				{
					t_vector3 hit_point = ray_at(&ray, t_cap);
					t_vector3 to_center = vector3_subtract(hit_point, top_center);
					double r2 = vector3_dot(to_center, to_center);
					if (r2 <= radius * radius + RT_EPS)
					{
						t_vector3 hit_normal = axis; // normal points outward
						if (vector3_dot(hit_normal, ray.dir) > 0.0)
							hit_normal = vector3_negate(hit_normal);
						if (!has_hit || t_cap < best_t)
						{
							has_hit = 1;
							best_t = t_cap;
							best_hit.t = t_cap;
							best_hit.hitPoint = hit_point;
							best_hit.normal = hit_normal;
							best_hit.material = &obj->material;
						}
					}
				}
			}

			// Bottom cap
			{
				double t_cap = vector3_dot(vector3_subtract(bottom_center, ray.orig), axis) / denom;
				if (t_cap >= t_min && t_cap <= t_max)
				{
					t_vector3 hit_point = ray_at(&ray, t_cap);
					t_vector3 to_center = vector3_subtract(hit_point, bottom_center);
					double r2 = vector3_dot(to_center, to_center);
					if (r2 <= radius * radius + RT_EPS)
					{
						t_vector3 hit_normal = vector3_negate(axis); // normal points outward
						if (vector3_dot(hit_normal, ray.dir) > 0.0)
							hit_normal = vector3_negate(hit_normal);
						if (!has_hit || t_cap < best_t)
						{
							has_hit = 1;
							best_t = t_cap;
							best_hit.t = t_cap;
							best_hit.hitPoint = hit_point;
							best_hit.normal = hit_normal;
							best_hit.material = &obj->material;
						}
					}
				}
			}
		}
	}

	if (!has_hit)
		return (0);
	*out = best_hit;
	out->object = obj;
	return (1);
}

static void cylinder_translate(t_object *obj, t_vector3 delta)
{
	t_cylinder *c = (t_cylinder*)obj;
	c->center = vector3_add(c->center, delta);
}

static void cylinder_rotate(t_object *obj, double rx, double ry, double rz)
{
	t_cylinder *c = (t_cylinder*)obj;
	c->orientation = rotate_euler_vec(c->orientation, rx, ry, rz);
	if (!vector3_normalize_safe(c->orientation, &c->axis_unit, RT_EPS))
		c->axis_unit = vector3_unit_y();
}

static void cylinder_scale_uniform(t_object *obj, double factor)
{
	t_cylinder *c = (t_cylinder*)obj;
	double d = c->diameter * factor;
	if (d > RT_MIN_OBJECT_EXTENT)
		c->diameter = d;
}

static void cylinder_scale_height(t_object *obj, double factor)
{
	t_cylinder *c = (t_cylinder*)obj;
	double h = c->height * factor;
	if (h > RT_MIN_OBJECT_EXTENT)
		c->height = h;
}

int	cylinder_init(t_cylinder *cylinder, t_vector3 center, t_vector3 orientation,
			double diameter, double height, t_material material)
{
	if (!cylinder)
	{
		printf("Error: Invalid cylinder pointer\n");
		return (1);
	}
	if (diameter <= 0 || height <= 0)
	{
		printf("Error: Cylinder diameter and height must be positive\n");
		return (1);
	}
	// compute normalized axis but also preserve raw orientation
	if (!vector3_normalize_safe(orientation, &cylinder->axis_unit, RT_EPS))
		return (1);
	object_init(&cylinder->base, CYLINDER, material,
		(t_object_funcs){&intersect_cylinder, &cylinder_translate,
		&cylinder_rotate, &cylinder_scale_uniform, &cylinder_scale_height});
	cylinder->center = center;
	cylinder->orientation = orientation;
	cylinder->diameter = diameter;
	cylinder->height = height;
	return (0);
}
