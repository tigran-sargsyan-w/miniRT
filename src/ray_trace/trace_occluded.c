/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_occluded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:07:09 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 22:33:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
#include "object.h"

/**
 * @brief Checks if single object occludes the ray
 * @param obj - object to test
 * @param ray - shadow ray
 * @param range - valid distance range
 * @return int - 1 if occluded, 0 otherwise
 */
static int	check_occlusion(const t_object *obj, t_ray ray, t_range range)
{
	t_hit	temp_hit;

	if (!obj->intersect_func)
		return (0);
	return (obj->intersect_func(obj, ray, range.min, range.max, &temp_hit));
}

/**
 * @brief Checks if any sphere occludes the ray
 * @param scene - scene containing spheres
 * @param ray - shadow ray
 * @param range - valid distance range
 * @return int - 1 if occluded by sphere, 0 otherwise
 */
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

/**
 * @brief Checks if any plane occludes the ray
 * @param scene - scene containing planes
 * @param ray - shadow ray
 * @param range - valid distance range
 * @return int - 1 if occluded by plane, 0 otherwise
 */
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

/**
 * @brief Checks if any cylinder occludes the ray
 * @param scene - scene containing cylinders
 * @param ray - shadow ray
 * @param range - valid distance range
 * @return int - 1 if occluded by cylinder, 0 otherwise
 */
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

/**
 * @brief Checks if ray is blocked by any object in scene
 * Used for shadow rays to determine if point is in shadow
 * @param scene - scene to test against
 * @param ray - shadow ray from hit point toward light
 * @param range - valid t range (eps to light distance)
 * @return int - 1 if occluded (in shadow), 0 if clear
 */
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
