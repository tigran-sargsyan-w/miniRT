/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:05:07 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 22:33:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "object.h"

/**
 * @brief Attempts to intersect ray with single object
 * Updates range.max if hit is closer than current best
 * @param obj - object to test
 * @param ray - ray to trace
 * @param range - valid distance range (modified on hit)
 * @param out_hit - stores hit info if intersection found
 * @return int - 1 if hit, 0 otherwise
 */
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

/**
 * @brief Tests ray against all spheres in scene
 * @param scene - scene containing spheres
 * @param ray - ray to trace
 * @param range - valid distance range
 * @param out_hit - stores closest hit info
 * @return int - 1 if any sphere hit, 0 otherwise
 */
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

/**
 * @brief Tests ray against all planes in scene
 * @param scene - scene containing planes
 * @param ray - ray to trace
 * @param range - valid distance range
 * @param out_hit - stores closest hit info
 * @return int - 1 if any plane hit, 0 otherwise
 */
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

/**
 * @brief Tests ray against all cylinders in scene
 * @param scene - scene containing cylinders
 * @param ray - ray to trace
 * @param range - valid distance range
 * @param out_hit - stores closest hit info
 * @return int - 1 if any cylinder hit, 0 otherwise
 */
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

/**
 * @brief Finds closest intersection of ray with scene
 * Main ray-scene intersection routine for primary rays
 * @param scene - scene to trace against
 * @param ray - ray to trace
 * @param range - valid t range [min, max]
 * @param out_hit - stores closest hit information
 * @return int - 1 if any object hit, 0 otherwise
 */
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
