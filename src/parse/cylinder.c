/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:38:57 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/31 22:41:42 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "cylinder.h"
#include "vector.h"
#include "color.h"
#include "material.h"
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
	double		tmp_center[3];
	double		tmp_ori[3];
	int			tmp_color[3];

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
	if (parse_vec3(tab[0], tmp_center) || parse_vec3(tab[1], tmp_ori)
		|| parse_color(tab[4], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	cy.center = vector3_create(tmp_center[0], tmp_center[1], tmp_center[2]);
	cy.orientation = vector3_create(tmp_ori[0], tmp_ori[1], tmp_ori[2]);
	cy.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1], (uint8_t)tmp_color[2]);
	// parse diameter
	{
		char *endptr = NULL;
		double val = strtod(tab[2], &endptr);
		if (endptr == tab[2])
		{
			ft_free_tab(tab);
			printf("Error: Invalid cylinder diameter\n");
			return (1);
		}
		cy.diameter = val;
	}
	// parse height
	{
		char *endptr = NULL;
		double val = strtod(tab[3], &endptr);
		if (endptr == tab[3])
		{
			ft_free_tab(tab);
			printf("Error: Invalid cylinder height\n");
			return (1);
		}
		cy.height = val;
	}
	if (cylinder_init(&cy, cy.center, cy.orientation, cy.diameter, cy.height,
			material_from_rgb8(cy.color)))
	{
		ft_free_tab(tab);
		return (1);
	}
	if (push_cylinder(scene, &cy))
	{
		ft_free_tab(tab);
		printf("Error: Memory allocation failed for cylinder\n");
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
