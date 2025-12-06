/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_range.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:47:19 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 00:41:11 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <stdio.h>

/**
 * @brief Validates camera orientation components and non-zero length
 * Range check: each component in [-1, 1], vector not zero
 * @param scene - scene with camera orientation to validate
 * @return int - 0 if valid, 1 on error
 */
int	validate_camera_orientation_range(t_scene *scene)
{
	t_vector3	ori;

	ori = scene->camera.orientation;
	if (ori.x < -1.0 || ori.x > 1.0 || ori.y < -1.0 || ori.y > 1.0
		|| ori.z < -1.0 || ori.z > 1.0)
	{
		printf("Error\nCamera orientation component out of range (-1.0 \
			- 1.0)\n");
		return (1);
	}
	if (vector3_length(ori) == 0.0)
	{
		printf("Error\nCamera orientation vector cannot be zero\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Validates orientation vectors of all cylinders in scene
 * Range check: each component in [-1, 1]
 * @param scene - scene with cylinders to validate
 * @return int - 0 if all valid, 1 on error
 */
int	validate_cylinder_orientation_range(t_scene *scene)
{
	int			i;
	t_vector3	ori;

	i = 0;
	while (i < scene->cylinder_count)
	{
		ori = scene->cylinders[i].orientation;
		if (ori.x < -1.0 || ori.x > 1.0 || ori.y < -1.0 || ori.y > 1.0
			|| ori.z < -1.0 || ori.z > 1.0)
		{
			printf("Error\nCylinder %d orientation component out of range \
				(-1.0 - 1.0)\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Validates numeric ranges for key scene parameters
 * Checks ambient/light intensity, camera FOV and orientations
 * @param scene - scene to validate
 * @return int - 0 if all values in range, 1 on error
 */
int	validate_input_range(t_scene *scene)
{
	if (scene->ambient.intensity < 0.0 || scene->ambient.intensity > 1.0)
	{
		printf("Error\nAmbient light intensity out of range (0.0 - 1.0)\n");
		return (1);
	}
	if (validate_camera_orientation_range(scene) != 0)
		return (1);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
	{
		printf("Error\nCamera FOV out of range (0 - 180)\n");
		return (1);
	}
	if (scene->light.intensity < 0.0 || scene->light.intensity > 1.0)
	{
		printf("Error\nLight intensity out of range (0.0 - 1.0)\n");
		return (1);
	}
	if (validate_cylinder_orientation_range(scene) != 0)
		return (1);
	return (0);
}
