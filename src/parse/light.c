/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:20:23 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/29 14:57:06 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "types.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>

int	parse_light(char *line, t_scene *scene)
{
	char	**tab;
	int		i;
	float	tmp_pos[3];
	int		col_int[3];

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	tab = ft_split(line, ' ');
	if (!tab)
		return (1);
	i = 0;
	while (tab[i])
		i++;
	if (i != 2 && i != 3)
	{
		ft_free_tab(tab);
		printf("Error: Invalid number of parameters for light\n");
		return (1);
	}
	if (parse_vec3(tab[0], tmp_pos))
	{
		ft_free_tab(tab);
		return (1);
	}
	/* set position (t_vector3) */
	scene->light.position = vector3_create((double)tmp_pos[0], (double)tmp_pos[1], (double)tmp_pos[2]);

	/* parse optional color (third token) - input is RGB 0..255; default to white */
	if (i == 3)
	{
		if (parse_color(tab[2], col_int))
		{
			ft_free_tab(tab);
			printf("Error: Invalid light color\n");
			return (1);
		}
	}
	else
	{
		col_int[0] = 255;
		col_int[1] = 255;
		col_int[2] = 255;
	}
	scene->light.color = color8_make((uint8_t)col_int[0], (uint8_t)col_int[1], (uint8_t)col_int[2]);
	// TODO: replace atof
	scene->light.intensity = atof(tab[1]);
	ft_free_tab(tab);
	return (0);
}
