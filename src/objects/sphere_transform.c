/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:53:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 14:28:35 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "sphere.h"
#include "transform.h"
#include "vector.h"

/**
 * @brief Translates sphere by delta vector
 * @param obj - sphere object
 * @param delta - translation offset
 */
void	sphere_translate(t_object *obj, t_vector3 delta)
{
	t_sphere	*s;

	s = (t_sphere *)obj;
	s->center = vector3_add(s->center, delta);
}

/**
 * @brief Rotation stub (sphere has no orientation)
 * @param obj - sphere object (unused)
 * @param rx - rotation X (unused)
 * @param ry - rotation Y (unused)
 * @param rz - rotation Z (unused)
 */
void	sphere_rotate(t_object *obj, double rx, double ry, double rz)
{
	(void)obj;
	(void)rx;
	(void)ry;
	(void)rz;
}

/**
 * @brief Uniformly scales sphere diameter
 * @param obj - sphere object
 * @param factor - scale factor
 */
void	sphere_scale_uniform(t_object *obj, double factor)
{
	t_sphere	*s;
	double		d;

	s = (t_sphere *)obj;
	d = s->diameter * factor;
	if (d > RT_MIN_OBJECT_EXTENT)
		s->diameter = d;
}

/**
 * @brief Height scale stub (sphere has no height)
 * @param obj - sphere object (unused)
 * @param factor - scale factor (unused)
 */
void	sphere_scale_height(t_object *obj, double factor)
{
	(void)obj;
	(void)factor;
}
