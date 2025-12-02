/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:47:39 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/02 22:16:54 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "scene.h"
# include "ray.h"
# include "hit.h"

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

int	scene_intersect(const t_scene *scene, t_ray ray,
		t_range range, t_hit *out_hit);
int	scene_occluded(const t_scene *scene, t_ray ray, t_range range);

#endif
