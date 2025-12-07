/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cache.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:31:32 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "camera.h"
#include "constants.h"
#include "render.h"

/**
 * @brief Compares camera basis vectors with cached values
 * @param cam - current camera
 * @param data - application state holding cached camera vectors
 * @return int - 1 if vectors are equal within EPS, 0 otherwise
 */
static int	check_cam_vecs(const t_camera *cam, const t_data *data)
{
	t_vector3	diff;

	diff = vector3_subtract(cam->forward, data->cam_fwd_cache);
	if (vector3_length(diff) > RT_EPS)
		return (0);
	diff = vector3_subtract(cam->right, data->cam_right_cache);
	if (vector3_length(diff) > RT_EPS)
		return (0);
	diff = vector3_subtract(cam->up, data->cam_up_cache);
	if (vector3_length(diff) > RT_EPS)
		return (0);
	return (1);
}

/**
 * @brief Checks whether cached ray directions are valid for current camera
 * Compares width/height, basis vectors and half sizes
 * @param cam - current camera
 * @param data - application state holding cache metadata
 * @return int - 1 if cache is valid, 0 otherwise
 */
int	cam_basis_equal(const t_camera *cam, const t_data *data)
{
	if (!data->ray_cache_valid)
		return (0);
	if (data->ray_cache_w != WIDTH || data->ray_cache_h != HEIGHT)
		return (0);
	if (!check_cam_vecs(cam, data))
		return (0);
	if (fabs(cam->half_width - data->cam_half_w_cache) > RT_EPS)
		return (0);
	if (fabs(cam->half_height - data->cam_half_h_cache) > RT_EPS)
		return (0);
	return (1);
}

/**
 * @brief Fills ray direction cache by computing direction for each pixel
 * @param data - application state with ray_dir_cache allocated
 * @param cam - camera used to calculate directions
 */
static void	fill_cache(t_data *data, const t_camera *cam)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calc_ray_dir(cam, x, y, &data->ray_dir_cache[y * WIDTH + x]);
			x++;
		}
		y++;
	}
}

/**
 * @brief Allocates and rebuilds cached ray directions for current camera
 * Also saves cache state for future equality checks
 * @param data - application state
 * @param cam - camera to build cache for
 * @return int - 0 on success, 1 on failure
 */
int	rebuild_ray_cache(t_data *data, const t_camera *cam)
{
	if (alloc_cache(data))
		return (1);
	fill_cache(data, cam);
	save_cache_state(data, cam);
	return (0);
}
