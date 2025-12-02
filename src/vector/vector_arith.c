/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:28:15 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:33:45 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * @brief Adds two vectors (a + b)
 * @param a - first vector
 * @param b - second vector
 * @return t_vector3 - sum of vectors
 */
t_vector3	vector3_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/**
 * @brief Subtracts second vector from first (a - b)
 * @param a - first vector
 * @param b - second vector
 * @return t_vector3 - difference of vectors
 */
t_vector3	vector3_subtract(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/**
 * @brief Negates vector (-v)
 * @param v - vector to negate
 * @return t_vector3 - negated vector
 */
t_vector3	vector3_negate(t_vector3 v)
{
	t_vector3	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}

/**
 * @brief Scales vector by scalar (v * k)
 * @param v - vector to scale
 * @param k - scalar multiplier
 * @return t_vector3 - scaled vector
 */
t_vector3	vector3_scale(t_vector3 v, double k)
{
	t_vector3	result;

	result.x = v.x * k;
	result.y = v.y * k;
	result.z = v.z * k;
	return (result);
}

/**
 * @brief Divides vector by scalar (v / k)
 * @param v - vector to divide
 * @param k - scalar divisor (must not be zero)
 * @return t_vector3 - divided vector
 */
t_vector3	vector3_divide_scalar(t_vector3 v, double k)
{
	t_vector3	result;

	result.x = v.x / k;
	result.y = v.y / k;
	result.z = v.z / k;
	return (result);
}
