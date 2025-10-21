/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:47:11 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 03:22:32 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

static void	debug_print_scene(t_scene *scene)
{
	t_sphere	*sp;

	printf("Scene Debug Info:\n");
	printf("Ambient Light: %d\n", scene->has_ambient);
	printf("Ambient Ratio: %.2f\n", scene->ambient.intensity);
	printf("Ambient Color: (%d, %d, %d)\n", scene->ambient.color[0],
		scene->ambient.color[1], scene->ambient.color[2]);
	printf("Camera: %d\n", scene->has_camera);
	printf("Light: %d\n", scene->has_light);
	printf("Number of Spheres: %d\n", scene->sphere_count);
	for (int i = 0; i < scene->sphere_count; ++i)
	{
		sp = scene->spheres[i];
		printf(" Sphere %d: Center(%.2f, %.2f, %.2f), Diameter: %.2f, Color(%d, \
			%d, %d)\n", i, sp->center[0], sp->center[1], sp->center[2],
			sp->diameter, sp->color[0], sp->color[1], sp->color[2]);
	}
}

int	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("Usage: %s <scene_file>\n", argv[0]);
		return (1);
	}
	if (argv[1][0] == '\0')
	{
		printf("Error: Empty filename\n");
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 3] != '.' || argv[1][len - 2] != 'r'
		|| argv[1][len - 1] != 't')
	{
		printf("Error: Filename must end with .rt\n");
		return (1);
	}
	return (0);
}

int	parse_obj_data(char *line, int type, t_scene *scene)
{
	// This function should handle parsing the object data based on the token
	if (type == AMBIENT)
		return (parse_ambient(line, scene));
	else if (type == CAMERA)
		return (parse_camera(line, scene));
	else if (type == LIGHT)
		return (parse_light(line, scene));
	else if (type == SPHERE)
		return (parse_sphere(line, scene));
	else if (type == PLANE)
		return (0); // parse_plane(line, scene);
	else if (type == CYLINDER)
		return (0); // parse_cylinder(line, scene);
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
		printf("Error: Multiple definitions of unique object type\n");
		return (1);
	}
	return (0);
}

int	check_parse_file(int fd, t_scene *scene)
{
	char	*line;
	char	*trimmed;
	char	*p;
	char	*token;
	int		obj_type;

	while ((line = get_next_line(fd)))
	{
		trimmed = ft_strtrim(line, " \t\r\n");
		p = trimmed;
		free(line);
		token = get_token(&p, " ");
		if (token)
		{
			obj_type = identify_object(token);
			if (obj_type != -1)
			{
				if (obj_count(scene, obj_type) || parse_obj_data(p, obj_type,
						scene))
				{
					free(token);
					free(trimmed);
					return (1);
				}
			}
			else
			{
				printf("Unknown object type: %s\n", token);
			}
			free(token);
		}
		free(trimmed);
	}
	debug_print_scene(scene);
	return (0);
}
