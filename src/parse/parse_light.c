/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:46:55 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 23:40:04 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "parse.h"
#include "scene.h"
#include <stdio.h>

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

static int	parse_light_position(t_scene *scene, double pos[3], char **tab)
{
	if (parse_vec3(tab[0], pos))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->light.position = vector3_create(pos[0], pos[1], pos[2]);
	return (0);
}

static int	parse_light_ratio(char **tab, double *ratio)
{
	char	*endptr;
	double	val;

	val = ft_strtod(tab[1], &endptr);
	if (endptr == tab[1])
	{
		ft_free_tab(tab);
		printf("Error\nInvalid light ratio\n");
		return (1);
	}
	if (*endptr != '\0')
	{
		ft_free_tab(tab);
		printf("Error\nInvalid light ratio: trailing characters at '%s'\n",
			endptr);
		return (1);
	}
	if (val < 0.0 || val > 1.0)
	{
		ft_free_tab(tab);
		printf("Error\nLight ratio out of range (0.0 to 1.0): %f\n", val);
		return (1);
	}
	*ratio = val;
	return (0);
}

static int	parse_light_color(t_scene *scene, char **tab, int col_int[3],
		int size)
{
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
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	char	**tab;
	int		size;
	double	pos[3];
	int		col_int[3];

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	if (split_light_line(line, &tab, &size))
		return (1);
	if (parse_light_position(scene, pos, tab))
		return (1);
	if (parse_light_ratio(tab, &scene->light.intensity))
		return (1);
	if (parse_light_color(scene, tab, col_int, size))
		return (1);
	ft_free_tab(tab);
	return (0);
}
