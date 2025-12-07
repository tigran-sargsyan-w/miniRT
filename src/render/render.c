/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:33:40 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include "minirt.h"
#include "camera.h"
#include "constants.h"
#include "render.h"

/**
 * @brief Initializes temporary camera struct from scene camera
 * Copies computed basis into scene camera after init
 * @param data - application state holding scene camera params
 * @param cam - output camera initialized for rendering
 * @return int - 0 on success, 1 on failure
 */
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

/**
 * @brief Allocates object pointer buffer used for outline detection
 * @param data - application state which will hold objbuf
 * @return int - 0 on success, 1 on allocation failure
 */
static int	alloc_objbuf(t_data *data)
{
	if (data->objbuf)
		return (0);
	data->objbuf = malloc(sizeof(*data->objbuf) * WIDTH * HEIGHT);
	if (!data->objbuf)
		return (1);
	return (0);
}

/**
 * @brief Top-level render entry: prepare camera, caches and draw image
 * Rebuilds ray cache when camera basis changed and draws outlines if needed
 * @param data - application state holding scene, caches and MLX
 * @return int - 0 on success, 1 on error
 */
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
