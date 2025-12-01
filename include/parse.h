#ifndef PARSE_H
# define PARSE_H

# include "scene.h"
# include <stdint.h>

int							check_args(int argc, char **argv);
char						*get_token(char **str, const char *delim);
int							identify_object(const char *token);
int							parse_camera(char *line, t_scene *scene);
int							parse_obj_data(char *line, int type,
								t_scene *scene);
int							obj_count(t_scene *scene, int obj_type);
int							check_parse_file(int fd, t_scene *scene);
int							parse_color(char *line, int color[3]);
int							parse_vec3(char *line, double vec[3]);
int							parse_ambient(char *line, t_scene *scene);
int							parse_camera(char *line, t_scene *scene);
int							parse_light(char *line, t_scene *scene);
int							parse_sphere(char *line, t_scene *scene);
int							parse_plane(char *line, t_scene *scene);
int							parse_cylinder(char *line, t_scene *scene);
int							parse_cylinder_diameter(char **tab, double *diameter);
int							parse_cylinder_height(char **tab, double *height);
int							validate_input_range(t_scene *scene);
void						ft_free_tab(char **tab);
int							ft_atoi_checked(const char *nptr, int *num);
char						*get_token(char **str, const char *delim);

#endif