/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:47:11 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/17 06:38:49 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include "types.h"
#include "parse.h"

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

int parse_vec3(char **line, float vec[3])
{
    char *token;
    
    token = get_token(line, " ");
    if (token)
    {
        vec[0] = atof(token);
        token = get_token(line, ",");
    }
    if (token)
    {
        vec[1] = atof(token);
        token = get_token(line, ",");
    }
    if (token)
        vec[2] = atof(token);
    free(token);
    return (0);
}

int parse_camera(char *line, t_scene *scene)
{
    // This function should handle parsing the camera data
    while (*line && ft_strchr(" \t\r\n", *line))
        line++;
    if (*line)
    {
        parse_vec3(&line, scene->camera.position);
        parse_vec3(&line, scene->camera.orientation);
        scene->camera.fov = atof(line);
    }
    printf("Camera Position: (%f, %f, %f)\n", scene->camera.position[0], scene->camera.position[1], scene->camera.position[2]);
    printf("Camera Orientation: (%f, %f, %f)\n", scene->camera.orientation[0], scene->camera.orientation[1], scene->camera.orientation[2]);
    printf("Camera FOV: %f\n", scene->camera.fov);
    return (0);
}

void parse_obj_data(char *line, int type, t_scene *scene)
{
    // This function should handle parsing the object data based on the token
    if (type == AMBIENT)
        parse_ambient(line, scene);
    else if (type == CAMERA)
        parse_camera(line, scene);
    else if (type == LIGHT)
        ; // parse_light(line, scene);
    else if (type == SPHERE)
        ; // parse_sphere(line, scene);
    else if (type == PLANE)
        ; // parse_plane(line, scene);
    else if (type == CYLINDER)
        ; // parse_cylinder(line, scene);
}

int obj_count(t_scene *scene, int obj_type)
{
    if (obj_type == AMBIENT)
        scene->has_ambient++;
    else if (obj_type == CAMERA)
        scene->has_camera++;
    else if (obj_type == LIGHT)
        scene->has_light++;
    else if (obj_type == SPHERE)
        scene->sphere_count++;
    else if (obj_type == PLANE)
        scene->plane_count++;
    else if (obj_type == CYLINDER)
        scene->cylinder_count++;
    if (scene->has_ambient > 1 || scene->has_camera > 1 || scene->has_light > 1)
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
    char *original_trimmed_line;
    char *token;

    while ((line = get_next_line(fd)))
    {
        trimmed_line = ft_strtrim(line, " \t\r\n");
        original_trimmed_line = trimmed_line;
        free(line);
        token = get_token(&trimmed_line, " ");
        if (token)
        {
            int obj_type = identify_object(token);
            if (obj_type != -1)
            {
                if (obj_count(scene, obj_type))
                {
                    free(token);
                    free(original_trimmed_line);
                    return (1);
                }
                parse_obj_data(trimmed_line, obj_type, scene);
            }
            else {
                // Call the appropriate parsing function based on obj_type
                printf("Unknown object type: %s\n", token);
            }
            free(token);
        }
        free(original_trimmed_line);
    }
    return (0);
}
