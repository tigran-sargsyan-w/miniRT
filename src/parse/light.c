#include "libft.h"
#include "parse.h"
#include "scene.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>

int	parse_light(char *line, t_scene *scene)
{
	char	**tab;
	int		i;
	double	tmp_pos[3];
	int		col_int[3];

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
	if (parse_vec3(tab[0], tmp_pos))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->light.position = vector3_create(tmp_pos[0], tmp_pos[1], tmp_pos[2]);

	// parse optional color (third token) - input is RGB 0..255; default to white
	if (i == 3)
	{
		if (parse_color(tab[2], col_int))
		{
			ft_free_tab(tab);
			printf("Error: Invalid light color\n");
			return (1);
		}
	}
	else
	{
		col_int[0] = 255;
		col_int[1] = 255;
		col_int[2] = 255;
	}
	scene->light.color = color8_make((uint8_t)col_int[0], (uint8_t)col_int[1], (uint8_t)col_int[2]);
	{
		char *endptr = NULL;
		double val = ft_strtod(tab[1], &endptr);
		if (endptr == tab[1])
		{
			ft_free_tab(tab);
			printf("Error: Invalid light intensity\n");
			return (1);
		}
		scene->light.intensity = val;
	}
	ft_free_tab(tab);
	return (0);
}
