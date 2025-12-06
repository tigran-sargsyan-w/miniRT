/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 14:19:42 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "object.h"
#include "plane.h"
#include "vector.h"
#include <math.h>

/**
 * @brief Fills hit record for plane intersection
 * @param out - hit record to fill
 * @param obj - plane object
 * @param ray - intersecting ray
 * @param t - hit distance
 */
static void	fill_plane_hit(t_hit *out, const t_object *obj,
		t_ray ray, double t)
{
	const t_plane	*plane;
	t_vector3		hit_point;
	t_vector3		hit_normal;

	plane = (const t_plane *)obj;
	hit_point = ray_at(&ray, t);
	hit_normal = plane->normal_unit;
	if (vector3_dot(hit_normal, ray.dir) > 0.0)
		hit_normal = vector3_negate(hit_normal);
	out->t = t;
	out->hitPoint = hit_point;
	out->normal = hit_normal;
	out->material = &obj->material;
	out->object = obj;
}

/**
 * @brief Ray intersection with infinite plane
 * Base formula: P = O + tD
 * Code equivalent: out->hitPoint = ray.orig + t * ray.dir;
 * @param obj - plane object
 * @param ray - ray to test
 * @param range - valid t range
 * @param out - stores hit information
 * @return int - 1 if hit, 0 otherwise
 */
static int	intersect_plane(const t_object *obj, t_ray ray,
		t_range range, t_hit *out)
{
	const t_plane	*plane;
	double			dir_dot_normal;
	double			t_hit;
	t_vector3		p_minus_o;

	if (!obj || !out)
		return (0);
	plane = (const t_plane *)obj;
	dir_dot_normal = vector3_dot(plane->normal_unit, ray.dir);
	if (fabs(dir_dot_normal) <= RT_EPS)
		return (0);
	p_minus_o = vector3_subtract(plane->point, ray.orig);
	t_hit = vector3_dot(p_minus_o, plane->normal_unit) / dir_dot_normal;
	if (t_hit < range.min || t_hit > range.max)
		return (0);
	fill_plane_hit(out, obj, ray, t_hit);
	return (1);
}

/**
 * @brief Initializes plane with point, normal and material
 * @param plane - plane structure to initialize
 * @param point - point on the plane
 * @param normal - plane normal direction
 * @param material - surface material
 * @return int - 0 on success, 1 on failure
 */
int	plane_init(t_plane *plane, t_vector3 point,
		t_vector3 normal, t_material material)
{
	t_object_funcs	funcs;

	if (!plane)
		return (1);
	if (!vector3_normalize_safe(normal, &plane->normal_unit, RT_EPS))
		return (1);
	funcs.intersect = &intersect_plane;
	funcs.translate = &plane_translate;
	funcs.rotate_euler = &plane_rotate;
	funcs.scale_uniform = &plane_scale_uniform;
	funcs.scale_height = &plane_scale_height;
	object_init(&plane->base, PLANE, material, funcs);
	plane->point = point;
	plane->normal = normal;
	return (0);
}
