/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:02:29 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 18:43:47 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

static int	split_vec3_line(char *line, char ***tab)
{
	int	n;

	*tab = ft_split(line, ',');
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
		printf("Error\nVector parsing error: expected 3 components, got %d\n",
			n);
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

static int	parse_vec3_components(char **tab, double vec[3])
{
	int		i;
	char	*endptr;
	double	value;

	i = -1;
	while (++i < 3)
	{
		endptr = NULL;
		value = ft_strtod(tab[i], &endptr);
		if (endptr == tab[i])
		{
			printf("Error\nVector component '%s' is not a number\n", tab[i]);
			ft_free_tab(tab);
			return (1);
		}
		if (*endptr != '\0')
		{
			printf("Error\nInvalid characters in vector component '%s'\n",
				tab[i]);
			ft_free_tab(tab);
			return (1);
		}
		vec[i] = value;
	}
	return (0);
}

int	parse_vec3(char *line, double vec[3])
{
	char	**tab;

	if (split_vec3_line(line, &tab))
		return (1);
	if (parse_vec3_components(tab, vec))
		return (1);
	ft_free_tab(tab);
	return (0);
}
