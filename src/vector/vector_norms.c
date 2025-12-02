/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:34:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 15:34:38 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

double	vector3_length_squared(t_vector3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vector3_length(t_vector3 v)
{
	return (sqrt(vector3_length_squared(v)));
}

int	vector3_normalize_safe(t_vector3 v, t_vector3 *out, double eps)
{
	double	len2;
	double	inv;

	len2 = vector3_length_squared(v);
	if (len2 <= eps * eps)
	{
		*out = VECTOR3_ZERO;
		return (0);
	}
	inv = 1.0 / sqrt(len2);
	out->x = v.x * inv;
	out->y = v.y * inv;
	out->z = v.z * inv;
	return (1);
}
