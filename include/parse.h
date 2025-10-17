#ifndef PARSE_H
# define PARSE_H

# include "types.h"
#include <stdint.h>

typedef union u_object_data
{
	t_sphere				sphere;
	t_plane					plane;
	t_cylinder				cylinder;
}							t_object_data;

typedef struct s_object_list
{
    int type;  
	t_object_data			data;
	struct s_object_list	*next;
}							t_object_list;

int							check_args(int argc, char **argv);
char						*get_token(char **str, const char *delim);
int							identify_object(const char *token);
int							parse_camera(char *line, t_scene *scene);
void						parse_obj_data(char *line, int type,
								t_scene *scene);
int							obj_count(t_scene *scene, int obj_type);
int							check_parse_file(int fd, t_scene *scene);
int							parse_color(char *line, int color[3]);
int							parse_vec3(char *line, float vec[3]);
int							parse_ambient(char *line, t_scene *scene);
int							parse_camera(char *line, t_scene *scene);
int							parse_light(char *line, t_scene *scene);
void						ft_free_tab(char **tab);
t_object_list				*node_create(t_object_data data);

#endif