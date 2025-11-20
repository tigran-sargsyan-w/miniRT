#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdio.h>
#include <stdlib.h>
#include "miniRT.h"
#include "object.h"

int	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("Error\nUsage: %s <scene_file>\n", argv[0]);
		return (1);
	}
	if (argv[1][0] == '\0')
	{
		printf("Error\nEmpty filename\n");
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 3 || argv[1][len - 3] != '.' || argv[1][len - 2] != 'r'
		|| argv[1][len - 1] != 't')
	{
		printf("Error\nFilename must end with .rt\n");
		return (1);
	}
	return (0);
}

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

int	check_parse_file(int fd, t_scene *scene)
{
	char	*line;
	char	*trimmed;
	char	*p;
	char	*token;
	int		obj_type;

	line = get_next_line(fd);
	if (!line)
	{
		printf("Error\nEmpty scene file\n");
		return (1);
	}
	while (line)
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
				printf("Error\nUnknown object type: %s\n", token);
				free(token);
				free(trimmed);
				return (1);
			}
			free(token);
		}
		free(trimmed);
		line = get_next_line(fd);
	}
	if (!scene->has_ambient || !scene->has_camera || !scene->has_light)
	{
		printf("Error\nMissing required object (ambient, camera, or light)\n");
		free(line);
		return (1);
	}
	free(line);
	return (0);
}
