#ifndef MINI_RT_H
# define MINI_RT_H
# include "scene.h"
# include "object.h"

#include "mlx_utils.h"

typedef struct s_data
{
	t_scene			scene;
	t_mlx_data		mlx;
	const t_object	*selected_object;
	const t_object	**objbuf;
	// Cached primary ray directions for current camera basis
	t_vector3		*ray_dir_cache; // size WIDTH*HEIGHT
	int				ray_cache_w;
	int				ray_cache_h;
	t_vector3		cam_fwd_cache;
	t_vector3		cam_right_cache;
	t_vector3		cam_up_cache;
	double			cam_half_w_cache;
	double			cam_half_h_cache;
	int				ray_cache_valid;
}					t_data;

int	check_args(int argc, char **argv);
int	check_parse_file(int fd, struct s_scene *scene);
int	validate_input_range(t_scene *scene);
void	debug_print_scene(t_scene *scene);

int     render_scene(t_data *data);
void    install_event_handlers(t_data *data);
void    free_scene(t_scene *scene);

#endif