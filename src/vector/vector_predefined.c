/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_predefined.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:57:54 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 15:57:59 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3	vector3_zero(void)
{
	return (vector3_create(0.0, 0.0, 0.0));
}

t_vector3	vector3_one(void)
{
	return (vector3_create(1.0, 1.0, 1.0));
}

t_vector3	vector3_unit_x(void)
{
	return (vector3_create(1.0, 0.0, 0.0));
}

t_vector3	vector3_unit_y(void)
{
	return (vector3_create(0.0, 1.0, 0.0));
}

t_vector3	vector3_unit_z(void)
{
	return (vector3_create(0.0, 0.0, 1.0));
}
