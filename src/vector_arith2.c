/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arith2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:30:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 15:30:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vector3	vector3_add_scaled(t_vector3 a, t_vector3 b, double k)
{
	t_vector3	result;

	result.x = a.x + k * b.x;
	result.y = a.y + k * b.y;
	result.z = a.z + k * b.z;
	return (result);
}

t_vector3	vector3_multiply_componentwise(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

t_vector3	vector3_divide_componentwise(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

int	vector3_divide_componentwise_safe(t_vector3 a, t_vector3 b,
		double eps, t_vector3 *out)
{
	if (fabs(b.x) <= eps || fabs(b.y) <= eps || fabs(b.z) <= eps)
	{
		*out = VECTOR3_ZERO;
		return (0);
	}
	out->x = a.x / b.x;
	out->y = a.y / b.y;
	out->z = a.z / b.z;
	return (1);
}
