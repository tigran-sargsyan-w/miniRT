/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 21:03:24 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 00:35:21 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>

/**
 * @brief Parses cylinder diameter from token and validates it
 * @param tab - token array (diameter at index 2)
 * @param diameter - out double diameter
 * @return int - 0 on success, 1 on error
 */
int	parse_cylinder_diameter(char **tab, double *diameter)
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

/**
 * @brief Parses cylinder height from token and validates it
 * @param tab - token array (height at index 3)
 * @param height - out double height
 * @return int - 0 on success, 1 on error
 */
int	parse_cylinder_height(char **tab, double *height)
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
