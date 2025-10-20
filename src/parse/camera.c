#include "libft.h"
#include "parse.h"
#include <stdio.h>

int parse_camera(char *line, t_scene *scene)
{
    char **tab;
    int i;

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
        printf("Error: Invalid number of parameters for camera\n");
        return (1);
    }
    if (parse_vec3(tab[0], scene->camera.position) ||
        parse_vec3(tab[1], scene->camera.orientation))
    {
        ft_free_tab(tab);
        return (1);
    }
    scene->camera.fov = ft_atoi(tab[2]);
    ft_free_tab(tab);
    return (0);
}