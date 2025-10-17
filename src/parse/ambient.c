#include "parse.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void ft_free_tab(char **tab)
{
    int i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int parse_ratio(char *str, float *ratio)
{
    char *endptr;
    float value;

    value = strtof(str, &endptr);
    if (endptr == str)
    {
        printf("Error: Invalid float value for ambient ratio\n");
        return (1);
    }
    *ratio = value;
    return (0);
}

int parse_color(char *line, int color[3])
{
    char **tab;
    int i;

    tab = ft_split(line, ',');
    if (!tab)
        return (1);
    i = 0;
    while (tab[i])
    {
        color[i] = atoi(tab[i]);
        i++;
    }
    ft_free_tab(tab);
    return (0);
}

int parse_ambient(char *line, t_scene *scene)
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
    if (i != 2)
    {
        printf("Error: Ambient light requires 2 parameters\n");
        ft_free_tab(tab);
        return (1);
    }
    if (parse_ratio(tab[0], &scene->ambient.intensity))
    {
        ft_free_tab(tab);
        return (1);
    }
    if (parse_color(tab[1], scene->ambient.color))
    {
        ft_free_tab(tab);
        return (1);
    }
    printf("ratio: %f\n", scene->ambient.intensity);
    printf("color: [%d, %d, %d]\n", scene->ambient.color[0], scene->ambient.color[1], scene->ambient.color[2]);
    ft_free_tab(tab);
    return (0);
}