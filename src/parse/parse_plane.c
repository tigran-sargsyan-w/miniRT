/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:47:10 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 22:46:31 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "material.h"
#include "parse.h"
#include "plane.h"
#include "scene.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

static int	push_plane(t_scene *s, t_plane *pl)
{
	t_plane	*arr;
	int		i;

	arr = malloc(sizeof(*arr) * (s->plane_count + 1));
	if (!arr)
		return (1);
	i = 0;
	while (i < s->plane_count)
	{
		arr[i] = s->planes[i];
		i++;
	}
	arr[s->plane_count] = *pl;
	free(s->planes);
	s->planes = arr;
	s->plane_count++;
	return (0);
}

static int	split_plane_line(char *line, char ***tab)
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
		printf("Error\nInvalid number of arguments for plane\n");
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

static int	parse_plane_components(char **tab, double point[3],
		double normal[3], int color[3])
{
	if (parse_vec3(tab[0], point))
		return (1);
	if (parse_vec3(tab[1], normal))
		return (1);
	if (parse_color(tab[2], color))
		return (1);
	return (0);
}

int	parse_plane(char *line, t_scene *scene)
{
	char	**tab;
	t_plane	plane;
	double	tmp_point[3];
	double	tmp_normal[3];
	int		tmp_color[3];

	if (split_plane_line(line, &tab))
		return (1);
	if (parse_plane_components(tab, tmp_point, tmp_normal, tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	plane.point = vector3_create(tmp_point[0], tmp_point[1], tmp_point[2]);
	plane.normal = vector3_create(tmp_normal[0], tmp_normal[1], tmp_normal[2]);
	plane.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1],
			(uint8_t)tmp_color[2]);
	if (plane_init(&plane, plane.point, plane.normal,
			material_from_rgb8(plane.color)) || push_plane(scene, &plane))
	{
		ft_free_tab(tab);
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
