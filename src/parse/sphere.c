/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:20:42 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 03:20:43 by dsemenov         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

static int	spheres_push(t_scene *s, t_sphere *sp)
{
	t_sphere	**arr;

	arr = malloc(sizeof(*arr) * (s->sphere_count + 1));
	if (!arr)
		return (1);
	for (int i = 0; i < s->sphere_count; ++i)
		arr[i] = s->spheres[i];
	arr[s->sphere_count] = sp;
	free(s->spheres);
	s->spheres = arr;
	s->sphere_count++;
	return (0);
}

int	parse_sphere(char *line, t_scene *scene)
{
	int			n;
	char		**tab;
	t_sphere	*sp;
	float		second;

	tab = ft_split(line, ' ');
	if (!tab)
		return (1);
	n = 0;
	while (tab[n])
		n++;
	if (n != 3)
	{
		ft_free_tab(tab);
		printf("Error: Invalid number of parameters for sphere\n");
		return (1);
	}
	sp = malloc(sizeof(*sp));
	if (!sp)
	{
		ft_free_tab(tab);
		return (1);
	}
	if (parse_vec3(tab[0], sp->center) || parse_color(tab[2], sp->color))
	{
		free(sp);
		ft_free_tab(tab);
		return (1);
	}
	second = atof(tab[1]);
	sp->diameter = second;
	if (spheres_push(scene, sp))
	{
		free(sp);
		ft_free_tab(tab);
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
