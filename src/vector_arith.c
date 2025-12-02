/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:28:15 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 15:28:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3	vector3_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	vector3_subtract(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	vector3_negate(t_vector3 v)
{
	t_vector3	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}

t_vector3	vector3_scale(t_vector3 v, double k)
{
	t_vector3	result;

	result.x = v.x * k;
	result.y = v.y * k;
	result.z = v.z * k;
	return (result);
}

t_vector3	vector3_divide_scalar(t_vector3 v, double k)
{
	t_vector3	result;

	result.x = v.x / k;
	result.y = v.y / k;
	result.z = v.z / k;
	return (result);
}
