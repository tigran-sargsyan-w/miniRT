/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:24:41 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 00:39:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

/**
 * @brief Routes object line to specific parse_*(ambient, camera, ...)
 * @param line - rest of the line after object id
 * @param type - object type enum
 * @param scene - scene to fill
 * @return int - 0 on success, 1 on error
 */
int	parse_obj_data(char *line, int type, t_scene *scene)
{
	if (type == AMBIENT)
		return (parse_ambient(line, scene));
	else if (type == CAMERA)
		return (parse_camera(line, scene));
	else if (type == LIGHT)
		return (parse_light(line, scene));
	else if (type == SPHERE)
		return (parse_sphere(line, scene));
	else if (type == PLANE)
		return (parse_plane(line, scene));
	else if (type == CYLINDER)
		return (parse_cylinder(line, scene));
	return (0);
}

/**
 * @brief Increments counters for unique objects and checks duplicates
 * Ensures only one ambient, camera and light exist in scene
 * @param scene - scene with has_* flags
 * @param obj_type - object type enum
 * @return int - 0 if OK, 1 on duplicate definition
 */
int	obj_count(t_scene *scene, int obj_type)
{
	if (obj_type == AMBIENT)
		scene->has_ambient++;
	else if (obj_type == CAMERA)
		scene->has_camera++;
	else if (obj_type == LIGHT)
		scene->has_light++;
	if (scene->has_ambient > 1 || scene->has_camera > 1 || scene->has_light > 1)
	{
		printf("Error\nMultiple definitions of unique object type\n");
		return (1);
	}
	return (0);
}
