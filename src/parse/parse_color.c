/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:52:44 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/28 19:00:08 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <stdio.h>

static int	color_split_line(char *line, char ***tab)
{
	int	i;

	*tab = ft_split(line, ',');
	i = 0;
	if (!*tab)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	while ((*tab)[i])
		i++;
	if (i != 3)
	{
		printf("Error\nColor parsing error: expected 3 components, got %d\n",
			i);
		ft_free_tab(*tab);
		return (1);
	}
	return (0);
}

int	parse_color(char *line, int color[3])
{
	char	**tab;
	int		i;

	if (color_split_line(line, &tab))
		return (1);
	i = 0;
	while (i < 3)
	{
		if (ft_atoi_checked(tab[i], &color[i]) || color[i] < 0
			|| color[i] > 255)
		{
			printf("Error\nColor parsing error: invalid value '%s'\n", tab[i]);
			ft_free_tab(tab);
			return (1);
		}
		i++;
	}
	ft_free_tab(tab);
	return (0);
}
