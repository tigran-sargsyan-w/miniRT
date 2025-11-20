#include "libft.h"
#include "parse.h"
#include <stdio.h>

int	parse_camera(char *line, t_scene *scene)
{
	char	**tab;
	int		i;

	double tmp_pos[3];
	double tmp_ori[3];

	while (*line && ft_strchr(" \t\r\n", *line))
		line++;
	tab = ft_split(line, ' ');
	if (!tab)
		return (1);
	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
	{
		ft_free_tab(tab);
		printf("Error\nInvalid number of parameters for camera\n");
		return (1);
	}
	if (parse_vec3(tab[0], tmp_pos) || parse_vec3(tab[1], tmp_ori))
	{
		ft_free_tab(tab);
		return (1);
	}
	scene->camera.position = vector3_create(tmp_pos[0], tmp_pos[1], tmp_pos[2]);
	scene->camera.orientation = vector3_create(tmp_ori[0], tmp_ori[1], tmp_ori[2]);
	scene->camera.fov = ft_atoi(tab[2]);
	ft_free_tab(tab);
	return (0);
}
