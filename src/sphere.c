/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:00:05 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/05 19:48:45 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "sphere.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void	sphere_translate(t_object *obj, t_vector3 delta);
void	sphere_rotate(t_object *obj, double rx, double ry, double rz);
void	sphere_scale_uniform(t_object *obj, double factor);
void	sphere_scale_height(t_object *obj, double factor);

static double	calc_discriminant(t_ray ray, t_vector3 center, double radius)
{
	t_vector3	oc;
	double		a;
	double		half_b;
	double		c;

	oc = vector3_subtract(ray.orig, center);
	a = vector3_dot(ray.dir, ray.dir);
	half_b = vector3_dot(oc, ray.dir);
	c = vector3_dot(oc, oc) - radius * radius;
	return (half_b * half_b - a * c);
}

static double	find_t_hit(t_ray ray, t_vector3 center, double radius,
		t_range range)
{
	t_vector3	oc;
	double		a;
	double		half_b;
	double		sqrt_disc;
	double		t;

	oc = vector3_subtract(ray.orig, center);
	a = vector3_dot(ray.dir, ray.dir);
	half_b = vector3_dot(oc, ray.dir);
	sqrt_disc = sqrt(half_b * half_b - a * (vector3_dot(oc, oc)
				- radius * radius));
	t = (-half_b - sqrt_disc) / a;
	if (t < range.min || t > range.max)
	{
		t = (-half_b + sqrt_disc) / a;
		if (t < range.min || t > range.max)
			return (-1.0);
	}
	return (t);
}

static void	fill_hit_record(t_hit *out, const t_object *obj,
		t_ray ray, double t)
{
	const t_sphere	*sphere;
	t_vector3		hit_point;
	t_vector3		normal;
	double			radius;

	sphere = (const t_sphere *)obj;
	radius = sphere->diameter * 0.5;
	hit_point = ray_at(&ray, t);
	normal = vector3_divide_scalar(vector3_subtract(hit_point, sphere->center),
			radius);
	if (vector3_dot(normal, ray.dir) > 0.0)
		normal = vector3_negate(normal);
	out->t = t;
	out->hitPoint = hit_point;
	out->normal = normal;
	out->material = &obj->material;
	out->object = obj;
}

static int	intersect_sphere(const t_object *obj, t_ray ray,
		t_range range, t_hit *out)
{
	const t_sphere	*sphere;
	double			radius;
	double			disc;
	double			t;

	if (!obj || !out)
		return (0);
	sphere = (const t_sphere *)obj;
	radius = sphere->diameter * 0.5;
	disc = calc_discriminant(ray, sphere->center, radius);
	if (disc < 0.0)
		return (0);
	t = find_t_hit(ray, sphere->center, radius, range);
	if (t < 0.0)
		return (0);
	fill_hit_record(out, obj, ray, t);
	return (1);
}

int	sphere_init(t_sphere *sphere, t_vector3 center,
		double diameter, t_material material)
{
	t_object_funcs	funcs;

	if (!sphere)
	{
		printf("Error: Invalid sphere pointer\n");
		return (1);
	}
	if (diameter <= 0.0)
	{
		printf("Error: Sphere diameter must be positive\n");
		return (1);
	}
	funcs.intersect = &intersect_sphere;
	funcs.translate = &sphere_translate;
	funcs.rotate_euler = &sphere_rotate;
	funcs.scale_uniform = &sphere_scale_uniform;
	funcs.scale_height = &sphere_scale_height;
	object_init(&sphere->base, SPHERE, material, funcs);
	sphere->center = center;
	sphere->diameter = diameter;
	return (0);
}
