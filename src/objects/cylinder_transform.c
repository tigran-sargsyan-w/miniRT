/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 00:08:57 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "cylinder.h"
#include "transform.h"
#include "vector.h"

void	cylinder_translate(t_object *obj, t_vector3 delta)
{
	t_cylinder	*c;

	c = (t_cylinder *)obj;
	c->center = vector3_add(c->center, delta);
}

void	cylinder_rotate(t_object *obj, double rx, double ry, double rz)
{
	t_cylinder	*c;

	c = (t_cylinder *)obj;
	c->orientation = rotate_euler_vec(c->orientation, rx, ry, rz);
	if (!vector3_normalize_safe(c->orientation, &c->axis_unit, RT_EPS))
		c->axis_unit = vector3_unit_y();
}

void	cylinder_scale_uniform(t_object *obj, double factor)
{
	t_cylinder	*c;
	double		d;

	c = (t_cylinder *)obj;
	d = c->diameter * factor;
	if (d > RT_MIN_OBJECT_EXTENT)
		c->diameter = d;
}

void	cylinder_scale_height(t_object *obj, double factor)
{
	t_cylinder	*c;
	double		h;

	c = (t_cylinder *)obj;
	h = c->height * factor;
	if (h > RT_MIN_OBJECT_EXTENT)
		c->height = h;
}
