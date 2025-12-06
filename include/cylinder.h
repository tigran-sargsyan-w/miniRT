/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:45 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/06 00:51:08 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "object.h"
# include "vector.h"
# include "color.h"
# include "material.h"

typedef struct s_cylinder
{
	t_object	base;
	t_vector3	center;
	t_vector3	orientation;
	t_vector3	axis_unit;
	double		diameter;
	double		height;
	t_color8	color;
}	t_cylinder;

int		cylinder_init(t_cylinder *cyl, t_material material);
void	cylinder_translate(t_object *obj, t_vector3 delta);
void	cylinder_rotate(t_object *obj, double rx, double ry, double rz);
void	cylinder_scale_uniform(t_object *obj, double factor);
void	cylinder_scale_height(t_object *obj, double factor);

#endif
