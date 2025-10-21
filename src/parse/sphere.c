/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:20:42 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 04:51:35 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

static int	spheres_push(t_scene *s, t_sphere *sp)
{
	t_sphere	*arr;
    int         i;

	arr = malloc(sizeof(*arr) * (s->sphere_count + 1));
	if (!arr)
		return (1);
    i = 0;
    while (i < s->sphere_count)
    {
        arr[i] = s->spheres[i];
        i++;
    }
	arr[s->sphere_count] = *sp;
	free(s->spheres);
	s->spheres = arr;
	s->sphere_count++;
	return (0);
}

int	parse_sphere(char *line, t_scene *scene)
{
	int			n;
	char		**tab;
	t_sphere	sp;

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
	if (parse_vec3(tab[0], sp.center) || parse_color(tab[2], sp.color))
	{
		ft_free_tab(tab);
		return (1);
	}
	sp.diameter = atof(tab[1]);
	if (spheres_push(scene, &sp))
	{
		ft_free_tab(tab);
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
