/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:46:55 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 22:46:27 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

static int	split_light_line(char *line, char ***tab, int *size)
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
	*size = n;
	if (n != 2 && n != 3)
	{
		printf("Error\nInvalid number of parameters for light\n");
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	char	**tab;
	int		size;
	double	tmp_pos[3];
	int		col_int[3];
	char	*endptr;
	double	val;

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	if (split_light_line(line, &tab, &size))
		return (1);
	if (parse_vec3(tab[0], tmp_pos))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->light.position = vector3_create(tmp_pos[0], tmp_pos[1], tmp_pos[2]);
	if (size == 3)
	{
		if (parse_color(tab[2], col_int))
		{
			ft_free_tab(tab);
			return (1);
		}
	}
	else
	{
		col_int[0] = 255;
		col_int[1] = 255;
		col_int[2] = 255;
	}
	scene->light.color = color8_make((uint8_t)col_int[0], (uint8_t)col_int[1],
			(uint8_t)col_int[2]);
	{
		endptr = NULL;
		val = ft_strtod(tab[1], &endptr);
		if (endptr == tab[1])
		{
			ft_free_tab(tab);
			printf("Error\nInvalid light intensity\n");
			return (1);
		}
		if (*endptr != '\0')
		{
			printf("Error\nInvalid light intensity: trailing characters starting at '%s'\n",
				endptr);
			ft_free_tab(tab);
			return (1);
		}
		scene->light.intensity = val;
	}
	ft_free_tab(tab);
	return (0);
}
