/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shadow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 16:29:46 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "hit.h"
#include "ray.h"
#include "vector.h"
#include "constants.h"
#include "trace.h"

int	is_in_shadow(const t_scene *scene, const t_hit *hit)
{
	t_vector3	l;
	double		dist;
	t_vector3	l_unit;
	t_vector3	shadow_origin;
	t_ray		shadow_ray;

	l = vector3_subtract(scene->light.position, hit->point);
	dist = vector3_length(l);
	if (!vector3_normalize_safe(l, &l_unit, RT_EPS))
		return (0);
	shadow_origin = vector3_add(hit->point,
			vector3_scale(hit->normal, K_SHADOW_BIAS));
	shadow_ray = ray_make(shadow_origin, l_unit);
	if (scene_occluded(scene, shadow_ray,
			(t_range){K_TMIN_PRIMARY, dist - K_SHADOW_BIAS}))
		return (1);
	return (0);
}
