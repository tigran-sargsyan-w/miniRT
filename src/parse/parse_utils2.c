/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:24:41 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 17:27:11 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

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
