/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:30:03 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 17:35:40 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>

int	parse_ratio(char *str, double *ratio)
{
	char	*endptr;
	double	value;

	value = ft_strtod(str, &endptr);
	if (endptr == str)
	{
		printf("Error\nInvalid double value for ambient ratio\n");
		return (1);
	}
	if (*endptr != '\0')
	{
		printf("Error\nInvalid trailing characters in ambient ratio\n");
		return (1);
	}
	*ratio = value;
	return (0);
}

static int	split_ambient_line(char *line, char ***tab)
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
	if (n != 2)
	{
		printf("Error\nAmbient light: expected 2 parameters, got %d\n", n);
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

int	parse_ambient(char *line, t_scene *scene)
{
	char	**tab;
	double	ratio_tmp;
	int		tmp_color[3];

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	if (split_ambient_line(line, &tab))
		return (1);
	if (parse_ratio(tab[0], &ratio_tmp))
	{
		printf("Error\nAmbient light ratio parsing failed\n");
		ft_free_tab(tab);
		return (1);
	}
	if (parse_color(tab[1], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->ambient.intensity = ratio_tmp;
	scene->ambient.color = color8_make((uint8_t)tmp_color[0],
			(uint8_t)tmp_color[1], (uint8_t)tmp_color[2]);
	ft_free_tab(tab);
	return (0);
}
