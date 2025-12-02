/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_predefined.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:57:54 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 17:34:55 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * @brief Returns zero vector (0, 0, 0)
 * @return t_vector3 - zero vector
 */
t_vector3	vector3_zero(void)
{
	return (vector3_create(0.0, 0.0, 0.0));
}

/**
 * @brief Returns unit vector (1, 1, 1)
 * @return t_vector3 - one vector
 */
t_vector3	vector3_one(void)
{
	return (vector3_create(1.0, 1.0, 1.0));
}

/**
 * @brief Returns X axis unit vector (1, 0, 0)
 * @return t_vector3 - unit X vector
 */
t_vector3	vector3_unit_x(void)
{
	return (vector3_create(1.0, 0.0, 0.0));
}

/**
 * @brief Returns Y axis unit vector (0, 1, 0)
 * @return t_vector3 - unit Y vector
 */
t_vector3	vector3_unit_y(void)
{
	return (vector3_create(0.0, 1.0, 0.0));
}

/**
 * @brief Returns Z axis unit vector (0, 0, 1)
 * @return t_vector3 - unit Z vector
 */
t_vector3	vector3_unit_z(void)
{
	return (vector3_create(0.0, 0.0, 1.0));
}
