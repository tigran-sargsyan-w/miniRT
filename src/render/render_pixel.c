/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 16:42:29 by tsargsya         ###   ########.fr       */
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

t_color	shade(const t_scene *scene, const t_hit *hit);
int		color_to_int(t_color c);
t_color	get_sky_color(t_ray ray);

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
