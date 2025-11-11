#include "libft.h"
#include "miniRT.h"
#include "scene.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx_utils.h"
#include <mlx.h>

void	free_scene(t_scene *scene)
{
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (check_args(argc, argv) != 0)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	if (check_parse_file(fd, &data.scene) != 0)
	{
		free_scene(&data.scene);
		close(fd);
		return (1);
	}
	close(fd);
	if (validate_input_range(&data.scene) != 0)
	{
		free_scene(&data.scene);
		return (1);
	}
	debug_print_scene(&data.scene); // For debugging purposes
	if (mlx_init_system(&data.mlx, "MiniRT") != 0)
	{
		free_scene(&data.scene);
		return (1);
	}
	if (render_scene(&data) != 0)
	{
		free_scene(&data.scene);
		mlx_destroy_all(&data.mlx);
		return (1);
	}
	install_event_handlers(&data);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.mlx.img.img_ptr, 0, 0);
	mlx_loop(data.mlx.mlx_ptr);
	free_scene(&data.scene);
	mlx_destroy_all(&data.mlx);
	return (0);
}
