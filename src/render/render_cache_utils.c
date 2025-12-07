/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cache_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:30:52 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "camera.h"
#include "constants.h"

/**
 * @brief Allocates ray direction cache array if not already allocated
 * @param data - application state which will hold ray_dir_cache
 * @return int - 0 on success, 1 on allocation failure
 */
int	alloc_cache(t_data *data)
{
	size_t	count;

	if (data->ray_dir_cache)
		return (0);
	count = (size_t)WIDTH * (size_t)HEIGHT;
	data->ray_dir_cache = malloc(sizeof(t_vector3) * count);
	if (!data->ray_dir_cache)
		return (1);
	return (0);
}

/**
 * @brief Computes a unit ray direction for pixel (x,y) from camera params
 * Uses center-of-pixel sampling (x+0.5, y+0.5)
 * @param cam - camera providing forward/right/up and half sizes
 * @param x - pixel X coordinate
 * @param y - pixel Y coordinate
 * @param out - out normalized direction vector
 */
void	calc_ray_dir(const t_camera *cam, int x, int y, t_vector3 *out)
{
	double		u;
	double		v;
	double		sx;
	double		sy;
	t_vector3	dir;

	u = ((double)x + 0.5) / (double)WIDTH * 2.0 - 1.0;
	v = 1.0 - ((double)y + 0.5) / (double)HEIGHT * 2.0;
	sx = u * cam->half_width;
	sy = v * cam->half_height;
	dir = vector3_add(cam->forward, vector3_scale(cam->right, sx));
	dir = vector3_add(dir, vector3_scale(cam->up, sy));
	if (!vector3_normalize_safe(dir, out, RT_EPS))
		*out = cam->forward;
}

/**
 * @brief Saves camera basis and sizes into data cache metadata
 * Marks `ray_cache_valid` as true
 * @param data - application state to update
 * @param cam - camera whose state to save
 */
void	save_cache_state(t_data *data, const t_camera *cam)
{
	data->ray_cache_w = WIDTH;
	data->ray_cache_h = HEIGHT;
	data->cam_fwd_cache = cam->forward;
	data->cam_right_cache = cam->right;
	data->cam_up_cache = cam->up;
	data->cam_half_w_cache = cam->half_width;
	data->cam_half_h_cache = cam->half_height;
	data->ray_cache_valid = 1;
}
