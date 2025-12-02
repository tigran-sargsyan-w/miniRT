/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:34:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:26:44 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

/**
 * @brief Computes squared length of vector - |v|^2
 * Faster than length() - avoids sqrt. Use for comparisons
 * @param v - input vector
 * @return double - squared length
 */
double	vector3_length_squared(t_vector3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

/**
 * @brief Computes length of vector - |v|
 * @param v - input vector
 * @return double - length (magnitude) of vector
 */
double	vector3_length(t_vector3 v)
{
	return (sqrt(vector3_length_squared(v)));
}

/**
 * @brief Safely normalizes vector to unit length
 * Returns zero vector if input is too small
 * @param v - vector to normalize
 * @param out - pointer to store normalized result
 * @param eps - minimum length threshold
 * @return int - 1 on success, 0 if vector too small
 */
int	vector3_normalize_safe(t_vector3 v, t_vector3 *out, double eps)
{
	double	len2;
	double	inv;

	len2 = vector3_length_squared(v);
	if (len2 <= eps * eps)
	{
		*out = vector3_zero();
		return (0);
	}
	inv = 1.0 / sqrt(len2);
	out->x = v.x * inv;
	out->y = v.y * inv;
	out->z = v.z * inv;
	return (1);
}
