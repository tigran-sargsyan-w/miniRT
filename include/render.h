/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 17:18:23 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <sys/time.h>
# include "minirt.h"
# include "camera.h"
# include "color.h"
# include "ray.h"
# include "hit.h"
# include "scene.h"

int		render_scene(t_data *data);
int		cam_basis_equal(const t_camera *cam, const t_data *data);
int		rebuild_ray_cache(t_data *data, const t_camera *cam);
int		alloc_cache(t_data *data);
void	calc_ray_dir(const t_camera *cam, int x, int y, t_vector3 *out);
void	save_cache_state(t_data *data, const t_camera *cam);
void	render_all_pixels_ext(t_data *data, t_camera *cam);
void	draw_outline(t_data *data);
void	debug_render_time(struct timeval start_time);
int		is_in_shadow(const t_scene *scene, const t_hit *hit);
t_color	shade(const t_scene *scene, const t_hit *hit);
int		color_to_int(t_color c);
t_color	get_sky_color(t_ray ray);

#endif
