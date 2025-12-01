/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:55:56 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 19:28:02 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object.h"
#include "parse.h"
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
		tab[i] = NULL;
		i++;
	}
	free(tab);
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
	else if (token[0] == '#')
		return (COMMENT);
	else
		return (-1);
}
