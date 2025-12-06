/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 23:02:52 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "constants.h"
#include "event_internal.h"
#include "camera.h"
#include "hit.h"
#include "ray.h"
#include "trace.h"
#include "mlx_utils.h"
#include <mlx.h>
#include <stddef.h>

static int	is_valid_click(t_data *data, int x, int y)
{
	if (!data || !data->scene.has_camera)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	return (1);
}

static void	handle_left_click(t_data *data, int x, int y)
{
	t_ray		ray;
	t_hit		hit;
	t_range		range;
	t_img_size	img_size;

	img_size.width = WIDTH;
	img_size.height = HEIGHT;
	ray = camera_ray(&data->scene.camera, x, y, img_size);
	range.min = K_TMIN_PRIMARY;
	range.max = K_TMAX_PRIMARY;
	if (scene_intersect(&data->scene, ray, range, &hit))
		data->selected_object = hit.object;
	else
		data->selected_object = NULL;
	render_and_display(data);
}

int	on_mouse(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!is_valid_click(data, x, y))
		return (0);
	if (button == 1)
		handle_left_click(data, x, y);
	return (0);
}
