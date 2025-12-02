/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_products.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:35:59 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:35:15 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * @brief Computes dot product (a · b)
 * Useful for angles, Lambert lighting, projections
 * @param a - first vector
 * @param b - second vector
 * @return double - dot product scalar
 */
double	vector3_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Computes cross product (a × b)
 * Returns perpendicular vector. Useful for normals, basis vectors
 * @param a - first vector
 * @param b - second vector
 * @return t_vector3 - cross product vector
 */
t_vector3	vector3_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
