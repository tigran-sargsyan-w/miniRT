/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 01:32:00 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_INTERNAL_H
# define CYLINDER_INTERNAL_H

# include "cylinder.h"
# include "hit.h"
# include "object.h"
# include "ray.h"

typedef struct s_cyl_hit_ctx
{
	const t_cylinder	*cyl;
	t_ray				ray;
	t_range				range;
	const t_object		*obj;
	int					has_hit;
	double				best_t;
	t_hit				best_hit;
}	t_cyl_hit_ctx;

typedef struct s_quad_coef
{
	double	a;
	double	b;
	double	c;
}	t_quad_coef;

int		check_side_hit(t_cyl_hit_ctx *ctx, double t);
int		check_cap_hit(t_cyl_hit_ctx *ctx, t_vector3 cap_center, int is_top);

#endif
