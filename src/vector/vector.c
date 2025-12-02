/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:25:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:35:37 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

/**
 * @brief Creates a new 3D vector with specified components
 * @param x - x component
 * @param y - y component
 * @param z - z component
 * @return t_vector3 - new vector (x, y, z)
 */
t_vector3	vector3_create(double x, double y, double z)
{
	t_vector3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * @brief Checks if all vector components are finite numbers
 * @param v - vector to check
 * @return int - 1 if all components finite, 0 otherwise
 */
int	vector3_is_finite(t_vector3 v)
{
	return ((isfinite(v.x) != 0) && (isfinite(v.y) != 0)
		&& (isfinite(v.z) != 0));
}

/**
 * @brief Compares two vectors with epsilon tolerance
 * @param a - first vector
 * @param b - second vector
 * @param eps - tolerance threshold
 * @return int - 1 if vectors are equal within eps, 0 otherwise
 */
int	vector3_equal_eps(t_vector3 a, t_vector3 b, double eps)
{
	if (fabs(a.x - b.x) > eps)
		return (0);
	if (fabs(a.y - b.y) > eps)
		return (0);
	if (fabs(a.z - b.z) > eps)
		return (0);
	return (1);
}

/**
 * @brief Checks if vector is near zero within epsilon
 * @param v - vector to check
 * @param eps - tolerance threshold
 * @return int - 1 if vector is near zero, 0 otherwise
 */
int	vector3_is_zero_eps(t_vector3 v, double eps)
{
	return ((fabs(v.x) <= eps) && (fabs(v.y) <= eps) && (fabs(v.z) <= eps));
}
