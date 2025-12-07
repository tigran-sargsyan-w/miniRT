/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:39:27 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 18:48:33 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"
# include "vector.h"

typedef struct s_img_size
{
	int		width;
	int		height;
}	t_img_size;

typedef struct s_cam_params
{
	t_vector3	position;
	t_vector3	look_dir;
	double		fov_deg;
}	t_cam_params;

typedef struct s_camera
{
	t_vector3	position;
	t_vector3	orientation;
	int			fov;
	t_vector3	forward;
	t_vector3	right;
	t_vector3	up;
	double		half_width;
	double		half_height;
}	t_camera;

int				camera_init(t_camera *camera, t_cam_params params,
					t_img_size img);
t_ray			camera_ray(const t_camera *camera, int px, int py,
					t_img_size img);

#endif
