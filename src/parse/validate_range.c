/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_range.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:22:45 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 05:28:42 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "types.h"

int	validate_color_range(int *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Error: Color component %d out of range (0 - 255)\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}
int validate_colors_range(t_scene *scene)
{
    int i;
	if (validate_color_range(scene->ambient.color) != 0)
    {
        printf("Error: Ambient light color out of range\n");
        return (1);
    }
    i = 0;
    while (i < scene->sphere_count)
    {
        if (validate_color_range(scene->spheres[i].color) != 0)
        {
            printf("Error: Sphere %d color out of range\n", i);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < scene->plane_count)
    {
        if (validate_color_range(scene->planes[i].color) != 0)
        {
            printf("Error: Plane %d color out of range\n", i);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < scene->cylinder_count)
    {
        if (validate_color_range(scene->cylinders[i].color) != 0)
        {
            printf("Error: Cylinder %d color out of range\n", i);
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
    if (scene->camera.fov < 0 || scene->camera.fov > 180)
    {
        printf("Error: Camera FOV out of range (0 - 180)\n");
        return (1);
    }
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
	{
		printf("Error: Light brightness out of range (0.0 - 1.0)\n");
		return (1);
	}
	return (0);
}
