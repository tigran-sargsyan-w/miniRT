/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:49 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 23:46:50 by dsemenov         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H
# include "vector.h"
# include "material.h"

// Forward declaration to avoid circular include with object.h
struct s_object;

typedef struct s_hit
{
	double				t;   // parameter t along the ray (like distance)
	t_vector3			hitPoint;   // intersection point
	t_vector3			normal;   // normal (unit vector)
	const t_material	*material; // material at the hit point
	const struct s_object	*object; // object that was hit (for selection/highlight)
}	t_hit;

#endif
