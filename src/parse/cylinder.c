/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:38:57 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 04:58:38 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

static int	push_cylinder(t_scene *s, t_cylinder *cy)
{
	t_cylinder	*arr;
	int			i;

	arr = malloc(sizeof(*arr) * (s->cylinder_count + 1));
	if (!arr)
		return (1);
	i = 0;
	while (i < s->cylinder_count)
	{
		arr[i] = s->cylinders[i];
		i++;
	}
	arr[s->cylinder_count] = *cy;
	free(s->cylinders);
	s->cylinders = arr;
	s->cylinder_count++;
	return (0);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char		**tab;
	t_cylinder	cy;
	int			n;

	tab = ft_split(line, ' ');
	if (!tab)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	n = 0;
	while (tab[n])
		n++;
	if (n != 5)
	{
		ft_free_tab(tab);
		printf("Error: Invalid number of parameters for cylinder\n");
		return (1);
	}
	if (parse_vec3(tab[0], cy.center) || parse_vec3(tab[1], cy.orientation)
		|| parse_color(tab[4], cy.color))
	{
		ft_free_tab(tab);
		return (1);
	}
	cy.diameter = atof(tab[2]);
	cy.height = atof(tab[3]);
	if (push_cylinder(scene, &cy))
	{
		ft_free_tab(tab);
		printf("Error: Memory allocation failed for cylinder\n");
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
