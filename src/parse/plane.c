/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:14:54 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 05:03:47 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "plane.h"
#include "vector.h"
#include "color.h"
#include "material.h"
#include "types.h"
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

int	parse_plane(char *line, t_scene *scene)
{
	char	**tab;
	t_plane	plane;
	int		n;
	float	tmp_point[3];
	float	tmp_normal[3];
	int		tmp_color[3];

	tab = ft_split(line, ' ');
	if (!tab)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	n = 0;
	while (tab[n])
		n++;
	if (n != 3)
	{
		printf("Error: Invalid number of arguments for plane\n");
		return (1);
	}
	if (parse_vec3(tab[0], tmp_point) || parse_vec3(tab[1], tmp_normal)
		|| parse_color(tab[2], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	plane.point = vector3_create((double)tmp_point[0], (double)tmp_point[1], (double)tmp_point[2]);
	plane.normal = vector3_create((double)tmp_normal[0], (double)tmp_normal[1], (double)tmp_normal[2]);
	plane.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1], (uint8_t)tmp_color[2]);
	if (plane_init(&plane, plane.point, plane.normal, material_from_rgb8(plane.color)))
	{
		ft_free_tab(tab);
		return (1);
	}
	if (push_plane(scene, &plane))
	{
		ft_free_tab(tab);
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
