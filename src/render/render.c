/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 16:52:35 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "minirt.h"
#include "camera.h"
#include "constants.h"

int		cam_basis_equal(const t_camera *cam, const t_data *data);
int		rebuild_ray_cache(t_data *data, const t_camera *cam);
void	render_all_pixels_ext(t_data *data, t_camera *cam);
void	draw_outline(t_data *data);
void	debug_render_time(struct timeval start_time);

static int	init_camera(t_data *data, t_camera *cam)
{
	t_cam_params	params;
	t_img_size		size;

	if (!data->scene.has_camera)
		return (1);
	params.position = data->scene.camera.position;
	params.look_dir = data->scene.camera.orientation;
	params.fov_deg = data->scene.camera.fov;
	size.width = WIDTH;
	size.height = HEIGHT;
	if (camera_init(cam, params, size))
		return (1);
	data->scene.camera.forward = cam->forward;
	data->scene.camera.right = cam->right;
	data->scene.camera.up = cam->up;
	data->scene.camera.half_width = cam->half_width;
	data->scene.camera.half_height = cam->half_height;
	return (0);
}

static int	alloc_objbuf(t_data *data)
{
	if (data->objbuf)
		return (0);
	data->objbuf = malloc(sizeof(*data->objbuf) * WIDTH * HEIGHT);
	if (!data->objbuf)
		return (1);
	return (0);
}

int	render_scene(t_data *data)
{
	t_camera		cam;
	struct timeval	start_time;

	if (!data)
		return (1);
	if (init_camera(data, &cam))
		return (1);
	if (alloc_objbuf(data))
		return (1);
	gettimeofday(&start_time, NULL);
	if (!cam_basis_equal(&cam, data))
		if (rebuild_ray_cache(data, &cam))
			return (1);
	render_all_pixels_ext(data, &cam);
	if (data->selected_object)
		draw_outline(data);
	debug_render_time(start_time);
	return (0);
}
