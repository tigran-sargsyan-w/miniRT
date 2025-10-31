/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_range.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:22:45 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/31 18:13:22 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "color.h"
#include <stdio.h>

int	validate_color_range(t_color8 color)
{
	// components are stored as uint8_t, range checks should be performed before casting
	(void)color;
	return (0);
}

int	validate_colors_range(t_scene *scene)
{
	int	i;

	if (validate_color_range(scene->ambient.color) != 0)
	{
		printf("Error: Ambient light color out of range\n");
		return (1);
	}
	i = 0;
	while (i < scene->sphere_count)
	{
		t_color8 col = scene->spheres[i].color;
		if (validate_color_range(col) != 0)
		{
			printf("Error: Sphere %d color out of range\n", i);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		t_color8 col = scene->planes[i].color;
		if (validate_color_range(col) != 0)
		{
			printf("Error: Plane %d color out of range\n", i);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		t_color8 col = scene->cylinders[i].color;
		if (validate_color_range(col) != 0)
		{
			printf("Error: Cylinder %d color out of range\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_camera_orientation_range(t_scene *scene)
{
	 t_vector3 ori = scene->camera.orientation;

	if (ori.x < -1.0 || ori.x > 1.0
		|| ori.y < -1.0 || ori.y > 1.0
		|| ori.z < -1.0 || ori.z > 1.0)
	{
		printf("Error: Camera orientation component out of range (-1.0 - 1.0)\n");
		return (1);
	}
	return (0);
}

int	validate_cylinder_orientation_range(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		t_vector3 ori = scene->cylinders[i].orientation;
		if (ori.x < -1.0 || ori.x > 1.0
			|| ori.y < -1.0 || ori.y > 1.0
			|| ori.z < -1.0 || ori.z > 1.0)
		{
			printf("Error: Cylinder %d orientation component out of range \
				(-1.0 - 1.0)\n",
					i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_input_range(t_scene *scene)
{
	if (scene->ambient.intensity < 0.0 || scene->ambient.intensity > 1.0)
	{
		printf("Error: Ambient light intensity out of range (0.0 - 1.0)\n");
		return (1);
	}
	if (validate_colors_range(scene) != 0)
		return (1);
	if (validate_camera_orientation_range(scene) != 0)
		return (1);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
	{
		printf("Error: Camera FOV out of range (0 - 180)\n");
		return (1);
	}
	if (scene->light.intensity < 0.0 || scene->light.intensity > 1.0)
	{
		printf("Error: Light intensity out of range (0.0 - 1.0)\n");
		return (1);
	}
	if (validate_cylinder_orientation_range(scene) != 0)
		return (1);
	return (0);
}
