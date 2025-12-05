/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:12 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/05 20:31:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "object.h"

typedef struct s_plane
{
	t_object	base;
	t_vector3	point;
	t_vector3	normal;
	t_vector3	normal_unit;
	t_color8	color;
}				t_plane;

int				plane_init(t_plane *plane, t_vector3 point, t_vector3 normal,
					t_material material);
void			plane_translate(t_object *obj, t_vector3 delta);
void			plane_rotate(t_object *obj, double rx, double ry, double rz);
void			plane_scale_uniform(t_object *obj, double factor);
void			plane_scale_height(t_object *obj, double factor);

#endif
