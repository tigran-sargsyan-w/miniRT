/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:37:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:35:34 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

/**
 * @brief Returns absolute value of each component
 * @param v - input vector
 * @return t_vector3 - vector with absolute values
 */
t_vector3	vector3_abs(t_vector3 v)
{
	t_vector3	result;

	result.x = fabs(v.x);
	result.y = fabs(v.y);
	result.z = fabs(v.z);
	return (result);
}

/**
 * @brief Component-wise minimum of two vectors
 * @param a - first vector
 * @param b - second vector
 * @return t_vector3 - min(a.x,b.x), min(a.y,b.y), min(a.z,b.z)
 */
t_vector3	vector3_min(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = fmin(a.x, b.x);
	result.y = fmin(a.y, b.y);
	result.z = fmin(a.z, b.z);
	return (result);
}

/**
 * @brief Component-wise maximum of two vectors
 * @param a - first vector
 * @param b - second vector
 * @return t_vector3 - max(a.x,b.x), max(a.y,b.y), max(a.z,b.z)
 */
t_vector3	vector3_max(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = fmax(a.x, b.x);
	result.y = fmax(a.y, b.y);
	result.z = fmax(a.z, b.z);
	return (result);
}

/**
 * @brief Clamps all components to [mn, mx] range
 * Useful for color clamping to [0, 1]
 * @param v - input vector
 * @param mn - minimum value
 * @param mx - maximum value
 * @return t_vector3 - clamped vector
 */
t_vector3	vector3_clamp(t_vector3 v, double mn, double mx)
{
	t_vector3	result;

	result = v;
	if (result.x < mn)
		result.x = mn;
	else if (result.x > mx)
		result.x = mx;
	if (result.y < mn)
		result.y = mn;
	else if (result.y > mx)
		result.y = mx;
	if (result.z < mn)
		result.z = mn;
	else if (result.z > mx)
		result.z = mx;
	return (result);
}

/**
 * @brief Linear interpolation between two vectors
 * Result = a*(1-t) + b*t
 * @param a - start vector (t=0)
 * @param b - end vector (t=1)
 * @param t - interpolation factor [0, 1]
 * @return t_vector3 - interpolated vector
 */
t_vector3	vector3_lerp(t_vector3 a, t_vector3 b, double t)
{
	t_vector3	result;

	result.x = a.x * (1.0 - t) + b.x * t;
	result.y = a.y * (1.0 - t) + b.y * t;
	result.z = a.z * (1.0 - t) + b.z * t;
	return (result);
}
