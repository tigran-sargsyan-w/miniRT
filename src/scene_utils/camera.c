/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:10:23 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/03 01:05:47 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "vector.h"
#include "constants.h"

static int	validate_cam_params(t_cam_params params, t_img_size img)
{
	if (img.width <= 0 || img.height <= 0)
		return (1);
	if (!isfinite(params.fov_deg) || params.fov_deg <= 0.0
		|| params.fov_deg >= 180.0)
		return (1);
	if (!vector3_is_finite(params.look_dir))
		return (1);
	return (0);
}

static int	setup_cam_basis(t_camera *cam, t_vector3 forward)
{
	t_vector3	world_up;
	t_vector3	right;

	world_up = vector3_unit_y();
	if (fabs(vector3_dot(forward, world_up)) > 0.999)
		world_up = vector3_unit_x();
	right = vector3_cross(world_up, forward);
	if (!vector3_normalize_safe(right, &right, RT_EPS))
		return (1);
	cam->right = right;
	cam->up = vector3_cross(forward, right);
	return (0);
}

int	camera_init(t_camera *cam, t_cam_params params, t_img_size img)
{
	t_vector3	forward;
	double		fov_rad;
	double		aspect;

	if (!cam || validate_cam_params(params, img))
		return (1);
	if (!vector3_normalize_safe(params.look_dir, &forward, RT_EPS))
		return (1);
	cam->position = params.position;
	cam->forward = forward;
	if (setup_cam_basis(cam, forward))
		return (1);
	fov_rad = params.fov_deg * (M_PI / 180.0);
	cam->half_width = tan(fov_rad * 0.5);
	aspect = (double)img.width / (double)img.height;
	if (!isfinite(aspect) || aspect <= 0.0)
		return (1);
	cam->half_height = cam->half_width / aspect;
	return (0);
}

// UV is NDC(Normalized Device Coordinates) mapped to [-1,1] range
t_ray	camera_ray(const t_camera *cam, int px, int py, t_img_size img)
{
	double		u;
	double		v;
	t_vector3	dir;
	t_vector3	ndir;

	u = ((double)px + 0.5) / (double)img.width * 2.0 - 1.0;
	v = 1.0 - ((double)py + 0.5) / (double)img.height * 2.0;
	dir = cam->forward;
	dir = vector3_add(dir, vector3_scale(cam->right, u * cam->half_width));
	dir = vector3_add(dir, vector3_scale(cam->up, v * cam->half_height));
	if (!vector3_normalize_safe(dir, &ndir, RT_EPS))
		ndir = cam->forward;
	return (ray_make(cam->position, ndir));
}
