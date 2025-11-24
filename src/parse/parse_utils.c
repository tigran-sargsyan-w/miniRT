#include "libft.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

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
	{	
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
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
		if (ft_atoi_checked(tab[i], &color[i]) || color[i] < 0 || color[i] > 255)
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

int	parse_vec3(char *line, double vec[3])
{
	char	**tab;
	int		n;

	tab = ft_split(line, ',');
	n = 0;
	if (!tab)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	while (tab[n])
		n++;
	if (n != 3)
	{
		printf("Error\nVector parsing error: expected 3 components, got %d\n", n);
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
			printf("Error\nVector component '%s' is not a number\n", tab[i]);
			ft_free_tab(tab);
			return (1);
		}
		if (*endptr != '\0')
		{
			printf("Error\nInvalid trailing characters in vector component '%s' (starts at '%s')\n", tab[i], endptr);
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
	else if (token[0] == '#')
		return (COMMENT); // Leave or remove comment handling?
	else
		return (-1);
}
