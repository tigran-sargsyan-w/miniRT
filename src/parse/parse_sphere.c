/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:47:15 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 00:39:00 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "material.h"
#include "parse.h"
#include "sphere.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Appends a new sphere to scene dynamic array
 * Reallocates and copies existing spheres
 * @param s - scene to modify
 * @param sp - sphere to append
 * @return int - 0 on success, 1 on allocation error
 */
static int	sphere_push(t_scene *s, t_sphere *sp)
{
	t_sphere	*arr;
	int			i;

	arr = malloc(sizeof(*arr) * (s->sphere_count + 1));
	if (!arr)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
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

/**
 * @brief Splits sphere line into center, diameter and color
 * Expects exactly 3 space-separated tokens
 * @param line - input line after identifier
 * @param tab - out array of 3 strings
 * @return int - 0 on success, 1 on error
 */
static int	split_sphere_line(char *line, char ***tab)
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
		printf("Error\nSphere: expected 3 parameters, got %d\n", n);
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

/**
 * @brief Parses and validates sphere diameter from token
 * Requires positive value
 * @param tab - token array (diameter at index 1)
 * @param diameter - out double diameter
 * @return int - 0 on success, 1 on error
 */
static int	parse_sphere_diameter(char **tab, double *diameter)
{
	char	*endptr;
	double	val;

	val = ft_strtod(tab[1], &endptr);
	if (endptr == tab[1])
	{
		ft_free_tab(tab);
		printf("Error\nInvalid double value for sphere diameter\n");
		return (1);
	}
	if (*endptr != '\0')
	{
		ft_free_tab(tab);
		printf("Error\nInvalid trailing characters in sphere diameter\n");
		return (1);
	}
	if (val <= 0.0)
	{
		ft_free_tab(tab);
		printf("Error\nSphere diameter must be positive\n");
		return (1);
	}
	*diameter = val;
	return (0);
}

/**
 * @brief Parses sphere definition line and adds to scene
 * @param line - line with center, diameter and color
 * @param scene - scene whose spheres array is extended
 * @return int - 0 on success, 1 on error
 */
int	parse_sphere(char *line, t_scene *scene)
{
	char		**tab;
	t_sphere	sp;
	double		tmp_center[3];
	int			tmp_color[3];

	if (split_sphere_line(line, &tab))
		return (1);
	if (parse_vec3(tab[0], tmp_center) || parse_color(tab[2], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	sp.center = vector3_create(tmp_center[0], tmp_center[1], tmp_center[2]);
	sp.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1],
			(uint8_t)tmp_color[2]);
	if (parse_sphere_diameter(tab, &sp.diameter))
		return (1);
	if (sphere_init(&sp, sp.center, sp.diameter, material_from_rgb8(sp.color))
		|| sphere_push(scene, &sp))
	{
		ft_free_tab(tab);
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
