/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arith2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:30:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:25:32 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

/**
 * @brief Computes a + k*b
 * Useful for ray_at: (origin + t*direction)
 * @param a - base vector
 * @param b - vector to scale and add
 * @param k - scalar multiplier for b
 * @return t_vector3 - result of a + k*b
 */
t_vector3	vector3_add_scaled(t_vector3 a, t_vector3 b, double k)
{
	t_vector3	result;

	result.x = a.x + k * b.x;
	result.y = a.y + k * b.y;
	result.z = a.z + k * b.z;
	return (result);
}

/**
 * @brief Component-wise multiplication (a.x*b.x, a.y*b.y, a.z*b.z)
 * Useful for color blending (a ⊙ b)
 * @param a - first vector
 * @param b - second vector
 * @return t_vector3 - component-wise product
 */
t_vector3	vector3_multiply_componentwise(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

/**
 * @brief Component-wise division (a.x/b.x, a.y/b.y, a.z/b.z)
 * Useful for certain calculations (a ⊘ b)
 * @param a - dividend vector
 * @param b - divisor vector (components must not be zero)
 * @return t_vector3 - component-wise quotient
 */
t_vector3	vector3_divide_componentwise(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

/**
 * @brief Safe component-wise division with zero check
 * @param a - dividend vector
 * @param b - divisor vector
 * @param eps - threshold for zero detection
 * @param out - pointer to store result
 * @return int - 1 on success, 0 if any b component near zero
 */
int	vector3_divide_componentwise_safe(t_vector3 a, t_vector3 b,
		double eps, t_vector3 *out)
{
	if (fabs(b.x) <= eps || fabs(b.y) <= eps || fabs(b.z) <= eps)
	{
		*out = vector3_zero();
		return (0);
	}
	out->x = a.x / b.x;
	out->y = a.y / b.y;
	out->z = a.z / b.z;
	return (1);
}
