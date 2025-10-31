/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:20:37 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/31 23:25:49 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>

char	*get_token(char **str, const char *delim)
{
	char	*start;
	char	*end;
	char	*token;
	size_t	len;

	if (!str || !*str)
		return (NULL);
	while (**str && ft_strchr(delim, **str))
		(*str)++;
	if (**str == '\0')
		return (NULL);
	start = *str;
	end = start;
	while (*end && !ft_strchr(delim, *end))
		end++;
	len = end - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	*str = end;
	return (token);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	parse_color(char *line, int color[3])
{
	char	**tab;
	int		n;
	int		i;

	tab = ft_split(line, ',');
	n = 0;
	if (!tab)
		return (1);
	while (tab[n])
		n++;
	if (n != 3)
	{
		ft_free_tab(tab);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (0);
}

int	parse_vec3(char *line, double vec[3])
{
	char	**tab;
	int		n;

	tab = ft_split(line, ',');
	n = 0;
	if (!tab)
		return (1);
	while (tab[n])
		n++;
	if (n != 3)
	{
		ft_free_tab(tab);
		return (1);
	}
	int i = 0;
	while (i < 3)
	{
		char *endptr = NULL;
		double value = ft_strtod(tab[i], &endptr);
		if (endptr == tab[i])
		{
			ft_free_tab(tab);
			return (1);
		}
		vec[i] = value;
		i++;
	}
	ft_free_tab(tab);
	return (0);
}

int	identify_object(const char *token)
{
	if (ft_strcmp(token, "A") == 0)
		return (AMBIENT);
	else if (ft_strcmp(token, "C") == 0)
		return (CAMERA);
	else if (ft_strcmp(token, "L") == 0)
		return (LIGHT);
	else if (ft_strcmp(token, "sp") == 0)
		return (SPHERE);
	else if (ft_strcmp(token, "pl") == 0)
		return (PLANE);
	else if (ft_strcmp(token, "cy") == 0)
		return (CYLINDER);
	else
		return (-1);
}
