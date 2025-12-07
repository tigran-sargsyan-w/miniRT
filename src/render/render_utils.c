/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 16:40:39 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include "color.h"
#include "ray.h"
#include "constants.h"

int	color_to_int(t_color c)
{
	t_color8	srgb;

	srgb = color_to_rgb8(color_clamp01(c));
	return ((srgb.r << 16) | (srgb.g << 8) | srgb.b);
}

t_color	get_sky_color(t_ray ray)
{
	double		tb;
	t_color		sky_top;
	t_color		sky_bottom;

	tb = K_SKY_BLEND_BIAS * (ray.dir.y + 1.0);
	sky_top = color_make(0.5, 0.5, 0.5);
	sky_bottom = color_make(0.0, 0.0, 0.0);
	return (color_lerp(sky_bottom, sky_top, tb));
}

void	debug_render_time(struct timeval start_time)
{
	struct timeval	end_time;
	double			render_ms;

	gettimeofday(&end_time, NULL);
	render_ms = (end_time.tv_sec - start_time.tv_sec) * 1000.0
		+ (end_time.tv_usec - start_time.tv_usec) / 1000.0;
	printf("Render time: %.2f ms\n", render_ms);
}
