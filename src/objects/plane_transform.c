/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 14:30:34 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "plane.h"
#include "transform.h"
#include "vector.h"

/**
 * @brief Translates plane by delta vector
 * @param obj - plane object
 * @param delta - translation offset
 */
void	plane_translate(t_object *obj, t_vector3 delta)
{
	t_plane	*pl;

	pl = (t_plane *)obj;
	pl->point = vector3_add(pl->point, delta);
}

/**
 * @brief Rotates plane normal by Euler angles
 * @param obj - plane object
 * @param rx - rotation around X axis (radians)
 * @param ry - rotation around Y axis (radians)
 * @param rz - rotation around Z axis (radians)
 */
void	plane_rotate(t_object *obj, double rx, double ry, double rz)
{
	t_plane		*pl;
	t_vector3	n;

	pl = (t_plane *)obj;
	n = rotate_euler_vec(pl->normal, rx, ry, rz);
	pl->normal = n;
	if (!vector3_normalize_safe(pl->normal, &pl->normal_unit, RT_EPS))
		pl->normal_unit = vector3_unit_y();
}

/**
 * @brief Scale stub (plane is infinite, no scale)
 * @param obj - plane object (unused)
 * @param factor - scale factor (unused)
 */
void	plane_scale_uniform(t_object *obj, double factor)
{
	(void)obj;
	(void)factor;
}

/**
 * @brief Height scale stub (plane has no height)
 * @param obj - plane object (unused)
 * @param factor - scale factor (unused)
 */
void	plane_scale_height(t_object *obj, double factor)
{
	(void)obj;
	(void)factor;
}
