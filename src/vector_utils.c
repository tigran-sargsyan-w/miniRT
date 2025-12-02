/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:37:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 15:37:41 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vector3	vector3_abs(t_vector3 v)
{
	t_vector3	result;

	result.x = fabs(v.x);
	result.y = fabs(v.y);
	result.z = fabs(v.z);
	return (result);
}

t_vector3	vector3_min(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = fmin(a.x, b.x);
	result.y = fmin(a.y, b.y);
	result.z = fmin(a.z, b.z);
	return (result);
}

t_vector3	vector3_max(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = fmax(a.x, b.x);
	result.y = fmax(a.y, b.y);
	result.z = fmax(a.z, b.z);
	return (result);
}

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

t_vector3	vector3_lerp(t_vector3 a, t_vector3 b, double t)
{
	t_vector3	result;

	result.x = a.x * (1.0 - t) + b.x * t;
	result.y = a.y * (1.0 - t) + b.y * t;
	result.z = a.z * (1.0 - t) + b.z * t;
	return (result);
}
