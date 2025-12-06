/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 01:20:30 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "cylinder_internal.h"
#include "vector.h"
#include <math.h>

static int	is_within_height(const t_cylinder *cyl, t_vector3 hit_point)
{
	t_vector3	center_to_point;
	double		axis_proj;

	center_to_point = vector3_subtract(hit_point, cyl->center);
	axis_proj = vector3_dot(center_to_point, cyl->axis_unit);
	return (fabs(axis_proj) <= (cyl->height * 0.5 + RT_EPS));
}

static t_vector3	calc_side_normal(const t_cylinder *cyl, t_vector3 hit_point)
{
	t_vector3	center_to_point;
	double		axis_proj;
	t_vector3	radial;
	t_vector3	normal;

	center_to_point = vector3_subtract(hit_point, cyl->center);
	axis_proj = vector3_dot(center_to_point, cyl->axis_unit);
	radial = vector3_subtract(center_to_point,
			vector3_scale(cyl->axis_unit, axis_proj));
	if (!vector3_normalize_safe(radial, &normal, RT_EPS))
		return (vector3_unit_y());
	return (normal);
}

static void	update_best_hit(t_cyl_hit_ctx *ctx, double t, t_vector3 normal)
{
	ctx->has_hit = 1;
	ctx->best_t = t;
	ctx->best_hit.t = t;
	ctx->best_hit.hitPoint = ray_at(&ctx->ray, t);
	ctx->best_hit.normal = normal;
	ctx->best_hit.material = &ctx->obj->material;
}

int	check_side_hit(t_cyl_hit_ctx *ctx, double t)
{
	t_vector3	hit_point;
	t_vector3	normal;

	if (t < ctx->range.min || t > ctx->range.max)
		return (0);
	hit_point = ray_at(&ctx->ray, t);
	if (!is_within_height(ctx->cyl, hit_point))
		return (0);
	normal = calc_side_normal(ctx->cyl, hit_point);
	if (vector3_dot(normal, ctx->ray.dir) > 0.0)
		normal = vector3_negate(normal);
	if (!ctx->has_hit || t < ctx->best_t)
	{
		update_best_hit(ctx, t, normal);
		return (1);
	}
	return (0);
}
