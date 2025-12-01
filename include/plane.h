/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:12 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 22:40:13 by dsemenov         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "object.h"

typedef struct s_plane
{
	t_object	base;
	t_vector3	point;
	// Raw normal as provided in scene (not normalized)
	t_vector3	normal;
	// Normalized unit normal for intersection/shading
	t_vector3	normal_unit;
	t_color8	color;
}				t_plane;

int				plane_init(t_plane *plane, t_vector3 point, t_vector3 normal,
					t_material material);

#endif
