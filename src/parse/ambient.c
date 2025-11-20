#include "libft.h"
#include "parse.h"
#include <stdio.h>

int	parse_ratio(char *str, double *ratio)
{
	char	*endptr;
	double	value;

	value = ft_strtod(str, &endptr);
	if (endptr == str)
	{
		printf("Error\nInvalid double value for ambient ratio\n");
		return (1);
	}
	*ratio = value;
	return (0);
}

int	parse_ambient(char *line, t_scene *scene)
{
	char	**tab;
	int			i;
	double		ratio_tmp;
	int			tmp_color[3];

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	tab = ft_split(line, ' ');
	if (!tab)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	i = 0;
	while (tab[i])
		i++;
	if (i != 2)
	{
		printf("Error\nAmbient light requires 2 parameters\n");
		ft_free_tab(tab);
		return (1);
	}
	if (parse_ratio(tab[0], &ratio_tmp))
	{
		printf("Error\nAmbient light ratio parsing failed\n");
		ft_free_tab(tab);
		return (1);
	}
	if (parse_color(tab[1], tmp_color))
	{
		printf("Error\nAmbient light color parsing failed\n");
		ft_free_tab(tab);
		return (1);
	}
	scene->ambient.intensity = ratio_tmp;
	scene->ambient.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1], (uint8_t)tmp_color[2]);
	ft_free_tab(tab);
	return (0);
}
