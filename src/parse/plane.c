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
	if (parse_vec3(tab[0], plane.point) || parse_vec3(tab[1], plane.normal)
		|| parse_color(tab[2], plane.color))
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
