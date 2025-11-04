#include "libft.h"
#include "miniRT.h"
#include "types.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx_utils.h"

void	free_scene(t_scene *scene)
{
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
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
	validate_input_range(&data.scene);//TODO: handle errors
	debug_print_scene(&data.scene); // For debugging purposes
	mlx_init_system(&data.mlx, "MiniRT");
	// TODO: Add rendering and event handling here
	free_scene(&data.scene);
	mlx_destroy_all(&data.mlx);
	return (0);
}
