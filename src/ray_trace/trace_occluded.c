/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_occluded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:07:09 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 22:01:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "object.h"

static int	check_occlusion(const t_object *obj, t_ray ray, t_range range)
{
	t_hit	temp_hit;

	if (!obj->intersect_func)
		return (0);
	return (obj->intersect_func(obj, ray, range.min, range.max, &temp_hit));
}

static int	occluded_by_spheres(const t_scene *scene, t_ray ray, t_range range)
{
	int	i;

	i = 0;
	while (i < scene->sphere_count)
	{
		if (check_occlusion((const t_object *)&scene->spheres[i], ray, range))
			return (1);
		i++;
	}
	return (0);
}

static int	occluded_by_planes(const t_scene *scene, t_ray ray, t_range range)
{
	int	i;

	i = 0;
	while (i < scene->plane_count)
	{
		if (check_occlusion((const t_object *)&scene->planes[i], ray, range))
			return (1);
		i++;
	}
	return (0);
}

static int	occluded_by_cylinders(const t_scene *scene, t_ray ray,
		t_range range)
{
	int	i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		if (check_occlusion((const t_object *)&scene->cylinders[i], ray, range))
			return (1);
		i++;
	}
	return (0);
}

int	scene_occluded(const t_scene *scene, t_ray ray, t_range range)
{
	if (occluded_by_spheres(scene, ray, range))
		return (1);
	if (occluded_by_planes(scene, ray, range))
		return (1);
	if (occluded_by_cylinders(scene, ray, range))
		return (1);
	return (0);
}
