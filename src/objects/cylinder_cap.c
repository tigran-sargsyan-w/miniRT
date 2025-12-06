/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 01:29:44 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "cylinder_internal.h"
#include "vector.h"
#include <math.h>

static double	calc_cap_t(t_ray ray, t_vector3 cap_center, t_vector3 axis)
{
	double		denom;
	t_vector3	diff;

	denom = vector3_dot(ray.dir, axis);
	if (fabs(denom) <= RT_EPS)
		return (-1.0);
	diff = vector3_subtract(cap_center, ray.orig);
	return (vector3_dot(diff, axis) / denom);
}

static int	is_within_cap_radius(t_vector3 hit, t_vector3 cap_c, double radius)
{
	t_vector3	to_center;
	double		r2;

	to_center = vector3_subtract(hit, cap_c);
	r2 = vector3_dot(to_center, to_center);
	return (r2 <= radius * radius + RT_EPS);
}

static void	update_cap_hit(t_cyl_hit_ctx *ctx, double t, t_vector3 normal)
{
	ctx->has_hit = 1;
	ctx->best_t = t;
	ctx->best_hit.t = t;
	ctx->best_hit.hitPoint = ray_at(&ctx->ray, t);
	ctx->best_hit.normal = normal;
	ctx->best_hit.material = &ctx->obj->material;
}

int	check_cap_hit(t_cyl_hit_ctx *ctx, t_vector3 cap_center, int is_top)
{
	double		t_cap;
	t_vector3	hit_point;
	t_vector3	normal;
	double		radius;

	t_cap = calc_cap_t(ctx->ray, cap_center, ctx->cyl->axis_unit);
	if (t_cap < ctx->range.min || t_cap > ctx->range.max)
		return (0);
	hit_point = ray_at(&ctx->ray, t_cap);
	radius = ctx->cyl->diameter * 0.5;
	if (!is_within_cap_radius(hit_point, cap_center, radius))
		return (0);
	if (is_top)
		normal = ctx->cyl->axis_unit;
	else
		normal = vector3_negate(ctx->cyl->axis_unit);
	if (vector3_dot(normal, ctx->ray.dir) > 0.0)
		normal = vector3_negate(normal);
	if (!ctx->has_hit || t_cap < ctx->best_t)
	{
		update_cap_hit(ctx, t_cap, normal);
		return (1);
	}
	return (0);
}
