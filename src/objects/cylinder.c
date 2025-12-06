/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 14:40:32 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "cylinder.h"
#include "cylinder_internal.h"
#include "object.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

/**
 * @brief Calculates quadratic coefficients for cylinder side
 * Gives quadratic at^2 + bt + c = 0
 * @param ctx - cylinder hit context
 * @param coef - output quadratic coefficients (a, b, c)
 */
static void	calc_quad_coef(t_cyl_hit_ctx *ctx, t_quad_coef *coef)
{
	t_vector3	oc;
	double		dir_dot_ax;
	double		oc_dot_ax;
	t_vector3	dir_perp;
	t_vector3	oc_perp;

	oc = vector3_subtract(ctx->ray.orig, ctx->cyl->center);
	dir_dot_ax = vector3_dot(ctx->ray.dir, ctx->cyl->axis_unit);
	oc_dot_ax = vector3_dot(oc, ctx->cyl->axis_unit);
	dir_perp = vector3_subtract(ctx->ray.dir,
			vector3_scale(ctx->cyl->axis_unit, dir_dot_ax));
	oc_perp = vector3_subtract(oc,
			vector3_scale(ctx->cyl->axis_unit, oc_dot_ax));
	coef->a = vector3_dot(dir_perp, dir_perp);
	coef->b = 2.0 * vector3_dot(dir_perp, oc_perp);
	coef->c = vector3_dot(oc_perp, oc_perp)
		- (ctx->cyl->diameter * 0.5) * (ctx->cyl->diameter * 0.5);
}

/**
 * @brief Checks both roots of quadratic for side hits
 * t = (-b ± sqrt(disc)) / 2a
 * @param ctx - cylinder hit context
 * @param coef - quadratic coefficients
 */
static void	check_side_roots(t_cyl_hit_ctx *ctx, t_quad_coef *coef)
{
	double	disc;
	double	sqrt_disc;
	double	t1;
	double	t2;

	if (fabs(coef->a) <= RT_EPS)
		return ;
	disc = coef->b * coef->b - 4.0 * coef->a * coef->c;
	if (disc < 0.0)
		return ;
	sqrt_disc = sqrt(disc);
	t1 = (-coef->b - sqrt_disc) / (2.0 * coef->a);
	t2 = (-coef->b + sqrt_disc) / (2.0 * coef->a);
	check_side_hit(ctx, t1);
	check_side_hit(ctx, t2);
}

/**
 * @brief Checks both top and bottom caps for hits
 * @param ctx - cylinder hit context
 */
static void	check_caps(t_cyl_hit_ctx *ctx)
{
	t_vector3	top_center;
	t_vector3	bottom_center;
	double		half_h;

	half_h = ctx->cyl->height * 0.5;
	top_center = vector3_add(ctx->cyl->center,
			vector3_scale(ctx->cyl->axis_unit, half_h));
	bottom_center = vector3_subtract(ctx->cyl->center,
			vector3_scale(ctx->cyl->axis_unit, half_h));
	check_cap_hit(ctx, top_center, 1);
	check_cap_hit(ctx, bottom_center, 0);
}

/**
 * @brief Ray intersection with cylinder (sides + caps)
 * Base formula: P = O + tD
 * Code equivalent: out->hitPoint = ray.orig + t * ray.dir;
 * @param obj - cylinder object
 * @param ray - ray to test
 * @param range - valid t range
 * @param out - stores hit information
 * @return int - 1 if hit, 0 otherwise
 */
static int	intersect_cylinder(const t_object *obj, t_ray ray,
		t_range range, t_hit *out)
{
	t_cyl_hit_ctx	ctx;
	t_quad_coef		coef;

	if (!obj || !out)
		return (0);
	ctx.cyl = (const t_cylinder *)obj;
	ctx.ray = ray;
	ctx.range = range;
	ctx.obj = obj;
	ctx.has_hit = 0;
	ctx.best_t = range.max;
	calc_quad_coef(&ctx, &coef);
	check_side_roots(&ctx, &coef);
	check_caps(&ctx);
	if (!ctx.has_hit)
		return (0);
	*out = ctx.best_hit;
	out->object = obj;
	return (1);
}

/**
 * @brief Initializes cylinder with geometry and material
 * Center, orientation, diameter, height must be set before call
 * @param cyl - cylinder structure to initialize
 * @param material - surface material
 * @return int - 0 on success, 1 on failure
 */
int	cylinder_init(t_cylinder *cyl, t_material material)
{
	t_object_funcs	funcs;

	if (!cyl)
	{
		printf("Error: Invalid cylinder pointer\n");
		return (1);
	}
	if (cyl->diameter <= 0 || cyl->height <= 0)
	{
		printf("Error: Cylinder diameter and height must be positive\n");
		return (1);
	}
	if (!vector3_normalize_safe(cyl->orientation, &cyl->axis_unit, RT_EPS))
		return (1);
	funcs.intersect = &intersect_cylinder;
	funcs.translate = &cylinder_translate;
	funcs.rotate_euler = &cylinder_rotate;
	funcs.scale_uniform = &cylinder_scale_uniform;
	funcs.scale_height = &cylinder_scale_height;
	object_init(&cyl->base, CYLINDER, material, funcs);
	return (0);
}
