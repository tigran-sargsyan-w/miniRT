/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:46:44 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 20:22:10 by dsemenov         ###   ########.fr       */
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

static int	parse_cylinder_diameter(char **tab, double *diameter)
{
	char	*endptr;
	double	val;

	val = ft_strtod(tab[2], &endptr);
	if (endptr == tab[2])
	{
		ft_free_tab(tab);
		printf("Error\nInvalid cylinder diameter\n");
		return (1);
	}
	if (*endptr != '\0')
	{
		ft_free_tab(tab);
		printf("Error\nInvalid cylinder diameter: trailing characters\n");
		return (1);
	}
	*diameter = val;
	return (0);
}

static int	parse_cylinder_height(char **tab, double *height)
{
	char	*endptr;
	double	val;

	val = ft_strtod(tab[3], &endptr);
	if (endptr == tab[3])
	{
		ft_free_tab(tab);
		printf("Error\nInvalid cylinder height\n");
		return (1);
	}
	if (*endptr != '\0')
	{
		ft_free_tab(tab);
		printf("Error\nInvalid cylinder height: trailing characters\n");
		return (1);
	}
	*height = val;
	return (0);
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
	if (parse_vec3(tab[0], tmp_center) || parse_vec3(tab[1], tmp_ori)
		|| parse_color(tab[4], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	cy.center = vector3_create(tmp_center[0], tmp_center[1], tmp_center[2]);
	cy.orientation = vector3_create(tmp_ori[0], tmp_ori[1], tmp_ori[2]);
	cy.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1],
			(uint8_t)tmp_color[2]);
	if (parse_cylinder_diameter(tab, &cy.diameter)
		|| parse_cylinder_height(tab, &cy.height))
		return (1);
	if (cylinder_init(&cy, cy.center, cy.orientation, cy.diameter, cy.height,
			material_from_rgb8(cy.color)))
	{
		ft_free_tab(tab);
		return (1);
	}
	if (push_cylinder(scene, &cy))
	{
		ft_free_tab(tab);
		printf("Error\nMemory allocation failed for cylinder\n");
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
