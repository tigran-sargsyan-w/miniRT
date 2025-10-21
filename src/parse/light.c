/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:20:23 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 03:21:02 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int	parse_light(char *line, t_scene *scene)
{
	char	**tab;
	int		i;

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	tab = ft_split(line, ' ');
	if (!tab)
		return (1);
	i = 0;
	while (tab[i])
		i++;
	if (i != 2 && i != 3)
	{
		ft_free_tab(tab);
		printf("Error: Invalid number of parameters for light\n");
		return (1);
	}
	if (parse_vec3(tab[0], scene->light.position))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->light.brightness = atof(tab[1]);
	ft_free_tab(tab);
	return (0);
}
