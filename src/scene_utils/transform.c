/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:15 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 21:02:00 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "transform.h"

/**
 * @brief Applies rotation around X axis (pitch)
 * @param v - pointer to vector to rotate
 * @param cx - cos(angle)
 * @param sx - sin(angle)
 */
static void	apply_rx(t_vector3 *v, double cx, double sx)
{
	double	tmp_y;

	tmp_y = v->y;
	v->y = v->y * cx - v->z * sx;
	v->z = tmp_y * sx + v->z * cx;
}

/**
 * @brief Applies rotation around Y axis (yaw)
 * @param v - pointer to vector to rotate
 * @param cy - cos(angle)
 * @param sy - sin(angle)
 */
static void	apply_ry(t_vector3 *v, double cy, double sy)
{
	double	tmp_x;

	tmp_x = v->x;
	v->x = v->x * cy + v->z * sy;
	v->z = -tmp_x * sy + v->z * cy;
}

/**
 * @brief Applies rotation around Z axis (roll)
 * @param v - pointer to vector to rotate
 * @param cz - cos(angle)
 * @param sz - sin(angle)
 */
static void	apply_rz(t_vector3 *v, double cz, double sz)
{
	double	tmp_x;

	tmp_x = v->x;
	v->x = v->x * cz - v->y * sz;
	v->y = tmp_x * sz + v->y * cz;
}

/**
 * @brief Rotates vector by Euler angles (XYZ order)
 * Used for rotating object orientations and normals
 * @param v - vector to rotate
 * @param rx - rotation around X axis in radians
 * @param ry - rotation around Y axis in radians
 * @param rz - rotation around Z axis in radians
 * @return t_vector3 - rotated vector
 */
t_vector3	rotate_euler_vec(t_vector3 v, double rx, double ry, double rz)
{
	apply_rx(&v, cos(rx), sin(rx));
	apply_ry(&v, cos(ry), sin(ry));
	apply_rz(&v, cos(rz), sin(rz));
	return (v);
}
