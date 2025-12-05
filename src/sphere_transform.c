/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:53:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/05 16:53:41 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "sphere.h"
#include "transform.h"
#include "vector.h"

void	sphere_translate(t_object *obj, t_vector3 delta)
{
	t_sphere	*s;

	s = (t_sphere *)obj;
	s->center = vector3_add(s->center, delta);
}

void	sphere_rotate(t_object *obj, double rx, double ry, double rz)
{
	(void)obj;
	(void)rx;
	(void)ry;
	(void)rz;
}

void	sphere_scale_uniform(t_object *obj, double factor)
{
	t_sphere	*s;
	double		d;

	s = (t_sphere *)obj;
	d = s->diameter * factor;
	if (d > RT_MIN_OBJECT_EXTENT)
		s->diameter = d;
}

void	sphere_scale_height(t_object *obj, double factor)
{
	(void)obj;
	(void)factor;
}
