/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:41:28 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 17:25:35 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "miniRT.h"
#include "object.h"
#include "parse.h"
#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

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

static int	handle_token(char *token, char *line, t_scene *scene)
{
	int	obj_type;

	obj_type = identify_object(token);
	if (obj_type == COMMENT)
		return (0);
	else if (obj_type != -1)
	{
		if (obj_count(scene, obj_type) || parse_obj_data(line, obj_type, scene))
			return (1);
	}
	else
	{
		printf("Error\nUnknown object type: %s\n", token);
		return (1);
	}
	return (0);
}

static int	process_line(char *trimmed, t_scene *scene)
{
	char	*p;
	char	*token;

	p = trimmed;
	token = get_token(&p, " \t\n");
	if (!token)
		return (1);
	if (handle_token(token, p, scene))
	{
		free(token);
		return (1);
	}
	free(token);
	return (0);
}

static int	gnl_loop(int fd, t_scene *scene, char **line)
{
	char	*trimmed;

	trimmed = ft_strtrim(*line, " \t\n");
	free(*line);
	if (!trimmed)
		return (1);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		*line = get_next_line(fd);
		return (0);
	}
	if (process_line(trimmed, scene))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	*line = get_next_line(fd);
	return (0);
}

int	check_parse_file(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		printf("Error\nEmpty scene file\n");
		return (1);
	}
	while (line)
	{
		if (gnl_loop(fd, scene, &line))
		{
			free(line);
			return (1);
		}
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
