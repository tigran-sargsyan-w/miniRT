/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:18:19 by dsemenov          #+#    #+#             */
/*   Updated: 2025/11/26 20:33:02 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "mlx_utils.h"
#include "scene.h"
#include <fcntl.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

static int	handle_parse_file(char *arg, t_scene *scene)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	if (check_parse_file(fd, scene) != 0)
	{
		free_scene(scene);
		close(fd);
		return (1);
	}
	close(fd);
	if (validate_input_range(scene) != 0)
	{
		free_scene(scene);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (check_args(argc, argv) != 0)
		return (1);
	if (handle_parse_file(argv[1], &data.scene) != 0)
		return (1);
	if (mlx_init_system(&data.mlx, "MiniRT") != 0 || render_scene(&data) != 0)
	{
		free(data.objbuf);
		free_scene(&data.scene);
		mlx_destroy_all(&data.mlx);
		return (1);
	}
	install_event_handlers(&data);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr,
		data.mlx.img.img_ptr, 0, 0);
	mlx_loop(data.mlx.mlx_ptr);
	free(data.objbuf);
	free_scene(&data.scene);
	mlx_destroy_all(&data.mlx);
	return (0);
}
