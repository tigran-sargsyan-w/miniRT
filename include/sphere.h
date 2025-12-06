/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:32 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/05 20:04:18 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "color.h"
# include "material.h"
# include "object.h"
# include "vector.h"

typedef struct s_sphere
{
	t_object	base;
	t_vector3	center;
	t_color8	color;
	double		diameter;
}				t_sphere;

int				sphere_init(t_sphere *sphere, t_vector3 center, double diameter,
					t_material material);
void			sphere_translate(t_object *obj, t_vector3 delta);
void			sphere_rotate(t_object *obj, double rx, double ry, double rz);
void			sphere_scale_uniform(t_object *obj, double factor);
void			sphere_scale_height(t_object *obj, double factor);

#endif
