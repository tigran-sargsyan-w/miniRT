/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:47:11 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/16 02:07:36 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include "types.h"

int check_args(int argc, char **argv)
{
    int len;
    if (argc != 2)
    {
        printf("Usage: %s <scene_file>\n", argv[0]);
        return (1);
    }
    if (argv[1][0] == '\0')
    {
        printf("Error: Empty filename\n");
        return (1);
    }
    len = ft_strlen(argv[1]);
    if (len < 4 || argv[1][len - 3] != '.' || argv[1][len - 2] != 'r' || argv[1][len - 1] != 't')
    {
        printf("Error: Filename must end with .rt\n");
        return (1);
    }
    return (0);
}

char *get_token(char **str, const char *delim)
{
    char *start;
    char *end;
    char *token;
    size_t len;

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

int identify_object(const char *token)
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

void parse_obj_data(char *line, char *token)
{
    // This function should handle parsing the object data based on the token
    // For now, it just prints the line and token
    printf("Parsing object data for token: %s\n", token);
    printf("Data: %s\n", line);
}

int obj_count(t_scene *scene, int obj_type)
{
    int ambient_count;
    int camera_count;
    int light_count;

    ambient_count = 0;
    camera_count = 0;
    light_count = 0;
    if (obj_type == AMBIENT)
        ambient_count++;
    else if (obj_type == CAMERA)
        camera_count++;
    else if (obj_type == LIGHT)
        light_count++;
    else if (obj_type == SPHERE)
        scene->sphere_count++;
    else if (obj_type == PLANE)
        scene->plane_count++;
    else if (obj_type == CYLINDER)
        scene->cylinder_count++;
    if (ambient_count > 1 || camera_count > 1 || light_count > 1)
    {
        printf("Error: Multiple definitions of unique object type\n");
        return (1);
    }
    return (0);
}

int check_parse_file(int fd, t_scene *scene)
{
    char *line;
    char *trimmed_line;
    char *token;

    while ((line = get_next_line(fd)))
    {
        trimmed_line = ft_strtrim(line, " \t\r\n");
        token = get_token(&trimmed_line, " ");
        if (token)
        {
            int obj_type = identify_object(token);
            if (obj_type != -1)
            {
                printf("Object type: %d\n", obj_type);
                printf("Read line: %s\n", trimmed_line);
                if (obj_count(scene, obj_type))
                {
                    free(token);
                    free(line);
                    free(trimmed_line);
                    return (1);
                }
                parse_obj_data(trimmed_line, token);
            }
            else {
                // Call the appropriate parsing function based on obj_type
                printf("Unknown object type: %s\n", token);
            }
            free(token);
        }
        free(line);
        //free(trimmed_line);
    }
    return (0);
}
