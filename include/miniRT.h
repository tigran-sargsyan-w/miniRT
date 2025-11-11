#ifndef MINI_RT_H
# define MINI_RT_H
# include "scene.h"

#include "mlx_utils.h"

typedef struct s_data
{
	t_scene			scene;
	t_mlx_data		mlx;
}					t_data;

int	check_args(int argc, char **argv);
int	check_parse_file(int fd, struct s_scene *scene);
int	validate_input_range(t_scene *scene);
void	debug_print_scene(t_scene *scene);

#endif