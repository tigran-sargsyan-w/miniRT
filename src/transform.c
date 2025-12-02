/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:21:15 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 19:21:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "transform.h"

static void	apply_rx(t_vector3 *v, double cx, double sx)
{
	double	tmp_y;

	tmp_y = v->y;
	v->y = v->y * cx - v->z * sx;
	v->z = tmp_y * sx + v->z * cx;
}

static void	apply_ry(t_vector3 *v, double cy, double sy)
{
	double	tmp_x;

	tmp_x = v->x;
	v->x = v->x * cy + v->z * sy;
	v->z = -tmp_x * sy + v->z * cy;
}

static void	apply_rz(t_vector3 *v, double cz, double sz)
{
	double	tmp_x;

	tmp_x = v->x;
	v->x = v->x * cz - v->y * sz;
	v->y = tmp_x * sz + v->y * cz;
}

t_vector3	rotate_euler_vec(t_vector3 v, double rx, double ry, double rz)
{
	apply_rx(&v, cos(rx), sin(rx));
	apply_ry(&v, cos(ry), sin(ry));
	apply_rz(&v, cos(rz), sin(rz));
	return (v);
}
