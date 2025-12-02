/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:05:07 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 22:09:47 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "object.h"

static int	try_hit_object(const t_object *obj, t_ray ray,
		t_range *range, t_hit *out_hit)
{
	t_hit	temp_hit;

	if (!obj->intersect_func)
		return (0);
	if (!obj->intersect_func(obj, ray, range->min, range->max, &temp_hit))
		return (0);
	range->max = temp_hit.t;
	*out_hit = temp_hit;
	out_hit->object = obj;
	return (1);
}

static int	intersect_spheres(const t_scene *scene, t_ray ray,
		t_range *range, t_hit *out_hit)
{
	int		i;
	int		hit_any;

	hit_any = 0;
	i = 0;
	while (i < scene->sphere_count)
	{
		if (try_hit_object((const t_object *)&scene->spheres[i],
				ray, range, out_hit))
			hit_any = 1;
		i++;
	}
	return (hit_any);
}

static int	intersect_planes(const t_scene *scene, t_ray ray,
		t_range *range, t_hit *out_hit)
{
	int		i;
	int		hit_any;

	hit_any = 0;
	i = 0;
	while (i < scene->plane_count)
	{
		if (try_hit_object((const t_object *)&scene->planes[i],
				ray, range, out_hit))
			hit_any = 1;
		i++;
	}
	return (hit_any);
}

static int	intersect_cylinders(const t_scene *scene, t_ray ray,
		t_range *range, t_hit *out_hit)
{
	int		i;
	int		hit_any;

	hit_any = 0;
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (try_hit_object((const t_object *)&scene->cylinders[i],
				ray, range, out_hit))
			hit_any = 1;
		i++;
	}
	return (hit_any);
}

int	scene_intersect(const t_scene *scene, t_ray ray,
		t_range range, t_hit *out_hit)
{
	int	hit_any;

	hit_any = 0;
	if (intersect_spheres(scene, ray, &range, out_hit))
		hit_any = 1;
	if (intersect_planes(scene, ray, &range, out_hit))
		hit_any = 1;
	if (intersect_cylinders(scene, ray, &range, out_hit))
		hit_any = 1;
	return (hit_any);
}
