/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shade.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 17:18:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "hit.h"
#include "color.h"
#include "vector.h"
#include "constants.h"
#include "render.h"

static t_color	calc_ambient(const t_scene *scene, t_color base)
{
	t_color	ambient_lin;

	ambient_lin = color_scale(color_from_rgb8(scene->ambient.color),
			scene->ambient.intensity);
	return (color_multiply(base, ambient_lin));
}

static int	get_light_dir(const t_scene *scene, const t_hit *hit,
		t_vector3 *l_unit)
{
	t_vector3	l;

	l = vector3_subtract(scene->light.position, hit->point);
	if (!vector3_normalize_safe(l, l_unit, RT_EPS))
		return (0);
	return (1);
}

static t_color	calc_diffuse(const t_scene *scene, const t_hit *hit,
		t_color base, t_vector3 l_unit)
{
	t_color	light_color;
	double	ndotl;
	double	diffuse;

	light_color = color_from_rgb8(scene->light.color);
	ndotl = vector3_dot(hit->normal, l_unit);
	if (ndotl <= 0.0)
		return (color_make(0, 0, 0));
	diffuse = ndotl * scene->light.intensity;
	if (diffuse < 0.0)
		diffuse = 0.0;
	return (color_scale(color_multiply(base, light_color), diffuse));
}

t_color	shade(const t_scene *scene, const t_hit *hit)
{
	t_color		base;
	t_color		result;
	t_vector3	l_unit;
	double		ndotl;

	base = hit->material->base_color;
	result = calc_ambient(scene, base);
	if (!scene->has_light || !hit || !hit->material)
		return (result);
	if (!get_light_dir(scene, hit, &l_unit))
		return (result);
	ndotl = vector3_dot(hit->normal, l_unit);
	if (ndotl <= 0.0)
		return (result);
	if (is_in_shadow(scene, hit))
		return (result);
	result = color_add(result, calc_diffuse(scene, hit, base, l_unit));
	return (result);
}
