#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# define WIDTH 800
# define HEIGHT 600

typedef struct s_img_data
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img_data;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				to_render;
	t_img_data		img;

}					t_mlx_data;

void	mlx_destroy_all(t_mlx_data *data);
int		mlx_init_system(t_mlx_data *data, char *name);
void	my_mlx_pixel_put(t_img_data *image_data, int x, int y, int color);

#endif