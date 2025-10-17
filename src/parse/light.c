#include "types.h"
#include "parse.h"
#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

int parse_light(char *line, t_scene *scene)
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
