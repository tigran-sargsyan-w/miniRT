/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:37:08 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 22:46:21 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>

static int	split_camera_line(char *line, char ***tab)
{
	int	n;

	*tab = ft_split(line, ' ');
	if (!*tab)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	n = 0;
	while ((*tab)[n])
		n++;
	if (n != 3)
	{
		printf("Error\nCamera: expected 3 parameters, got %d\n", n);
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

int	parse_camera(char *line, t_scene *scene)
{
	char	**tab;
	double	tmp_pos[3];
	double	tmp_ori[3];

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	if (split_camera_line(line, &tab))
		return (1);
	if (parse_vec3(tab[0], tmp_pos) || parse_vec3(tab[1], tmp_ori))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->camera.position = vector3_create(tmp_pos[0], tmp_pos[1], tmp_pos[2]);
	scene->camera.orientation = vector3_create(tmp_ori[0], tmp_ori[1],
			tmp_ori[2]);
	if (ft_atoi_checked(tab[2], &scene->camera.fov))
	{
		ft_free_tab(tab);
		printf("Error\nInvalid camera FOV\n");
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
