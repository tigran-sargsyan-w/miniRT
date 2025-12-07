/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:33:22 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minirt.h"
#include "object.h"
#include "color.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "constants.h"
#include "trace.h"
#include "render.h"

/**
 * @brief Renders single pixel at (x,y) by casting cached ray and shading
 * out-> Writes pixel color to MLX image and updates object buffer if selected
 * @param data - application state with scene, caches and MLX
 * @param cam - camera used for ray directions
 * @param x - pixel X coordinate
 * @param y - pixel Y coordinate
 */
static void	render_pixel(t_data *data, t_camera *cam, int x, int y)
{
	t_ray	ray;
	t_hit	htmp;
	t_color	col;
	int		packed;

	ray = ray_make(cam->position, data->ray_dir_cache[y * WIDTH + x]);
	if (scene_intersect(&data->scene, ray,
			(t_range){K_TMIN_PRIMARY, K_TMAX_PRIMARY}, &htmp))
	{
		if (data->selected_object)
			data->objbuf[y * WIDTH + x] = htmp.object;
		col = shade(&data->scene, &htmp);
	}
	else
	{
		if (data->selected_object)
			data->objbuf[y * WIDTH + x] = NULL;
		col = get_sky_color(ray);
	}
	packed = color_to_int(col);
	my_mlx_pixel_put(&data->mlx.img, x, y, packed);
}

/**
 * @brief Renders all pixels using an external (cached) camera
 * Iterates over the full image and calls render_pixel for each pixel
 * @param data - application state
 * @param cam - prepared camera with basis and half sizes
 */
void	render_all_pixels_ext(t_data *data, t_camera *cam)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(data, cam, x, y);
			x++;
		}
		y++;
	}
}
