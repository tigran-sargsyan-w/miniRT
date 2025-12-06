/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:46:44 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/06 01:38:01 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "cylinder.h"
#include "libft.h"
#include "material.h"
#include "parse.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

static int	push_cylinder(t_scene *s, t_cylinder *cy)
{
	t_cylinder	*arr;
	int			i;

	arr = malloc(sizeof(*arr) * (s->cylinder_count + 1));
	if (!arr)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
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

static int	split_cylinder_line(char *line, char ***tab)
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
	if (n != 5)
	{
		ft_free_tab(*tab);
		printf("Error\nInvalid number of parameters for cylinder\n");
		return (1);
	}
	return (0);
}

static int	parse_cylinder_components(char **tab, double *tmp_center,
		double *tmp_ori, int *tmp_color)
{
	if (parse_vec3(tab[0], tmp_center) || parse_vec3(tab[1], tmp_ori)
		|| parse_color(tab[4], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	return (0);
}

void	fill_cylinder_values(t_cylinder *cy, double *tmp_center,
		double *tmp_ori, int *tmp_color)
{
	cy->center = vector3_create(tmp_center[0], tmp_center[1], tmp_center[2]);
	cy->orientation = vector3_create(tmp_ori[0], tmp_ori[1], tmp_ori[2]);
	cy->color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1],
			(uint8_t)tmp_color[2]);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char		**tab;
	t_cylinder	cy;
	double		tmp_center[3];
	double		tmp_ori[3];
	int			tmp_color[3];

	if (split_cylinder_line(line, &tab))
		return (1);
	if (parse_cylinder_components(tab, tmp_center, tmp_ori, tmp_color))
		return (ft_free_tab(tab), 1);
	fill_cylinder_values(&cy, tmp_center, tmp_ori, tmp_color);
	if (parse_cylinder_diameter(tab, &cy.diameter)
		|| parse_cylinder_height(tab, &cy.height))
		return (1);
	if (cylinder_init(&cy, material_from_rgb8(cy.color))
		|| push_cylinder(scene, &cy))
		return (ft_free_tab(tab), 1);
	ft_free_tab(tab);
	return (0);
}
