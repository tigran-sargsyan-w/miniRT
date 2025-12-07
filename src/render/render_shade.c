/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shade.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:32:41 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "hit.h"
#include "color.h"
#include "vector.h"
#include "constants.h"
#include "render.h"

/**
 * @brief Calculates ambient contribution using scene ambient and base color
 * @param scene - scene ambient parameters
 * @param base - material base color
 * @return t_color - ambient-lit color component
 */
static t_color	calc_ambient(const t_scene *scene, t_color base)
{
	t_color	ambient_lin;

	ambient_lin = color_scale(color_from_rgb8(scene->ambient.color),
			scene->ambient.intensity);
	return (color_multiply(base, ambient_lin));
}

/**
 * @brief Computes (and normalizes) direction from hit point to light
 * @param scene - scene containing light position
 * @param hit - hit record with intersection point
 * @param l_unit - out normalized light direction
 * @return int - 1 if direction valid, 0 otherwise
 */
static int	get_light_dir(const t_scene *scene, const t_hit *hit,
		t_vector3 *l_unit)
{
	t_vector3	l;

	l = vector3_subtract(scene->light.position, hit->point);
	if (!vector3_normalize_safe(l, l_unit, RT_EPS))
		return (0);
	return (1);
}

/**
 * @brief Calculates diffuse lighting term for given hit and light dir
 * @param scene - scene with light color/intensity
 * @param hit - hit record with normal and material
 * @param base - base material color
 * @param l_unit - normalized light direction vector
 * @return t_color - diffuse contribution
 */
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

/**
 * @brief Computes shaded color at hit point combining ambient and diffuse
 * Performs shadow test and returns base ambient if in shadow or facing away
 * @param scene - scene with light and ambient
 * @param hit - hit record describing intersection
 * @return t_color - shaded color to be displayed
 */
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
