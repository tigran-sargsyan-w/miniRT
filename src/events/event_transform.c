/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 23:27:57 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "constants.h"
#include "event_internal.h"
#include "vector.h"
#include <math.h>

static t_vector3	get_translation_delta(int keycode)
{
	t_vector3	d;

	d = vector3_zero();
	if (keycode == KEY_A)
		d.x = -MOVE_STEP;
	else if (keycode == KEY_D)
		d.x = MOVE_STEP;
	else if (keycode == KEY_Q)
		d.y = MOVE_STEP;
	else if (keycode == KEY_E)
		d.y = -MOVE_STEP;
	else if (keycode == KEY_W)
		d.z = MOVE_STEP;
	else if (keycode == KEY_S)
		d.z = -MOVE_STEP;
	return (d);
}

int	handle_translation(t_data *data, int keycode)
{
	const t_object	*obj;
	t_vector3		d;

	obj = data->selected_object;
	if (!obj || !obj->translate)
		return (0);
	d = get_translation_delta(keycode);
	if (d.x == 0.0 && d.y == 0.0 && d.z == 0.0)
		return (0);
	obj->translate((t_object *)obj, d);
	return (1);
}

static void	get_rotation_angles(int keycode, double *rx, double *ry, double *rz)
{
	double	step;

	step = ROTATE_STEP_DEG * M_PI / 180.0;
	*rx = 0.0;
	*ry = 0.0;
	*rz = 0.0;
	if (keycode == KEY_I)
		*rx = step;
	else if (keycode == KEY_K)
		*rx = -step;
	else if (keycode == KEY_J)
		*ry = step;
	else if (keycode == KEY_L)
		*ry = -step;
	else if (keycode == KEY_U)
		*rz = step;
	else if (keycode == KEY_O)
		*rz = -step;
}

int	handle_rotation(t_data *data, int keycode)
{
	const t_object	*obj;
	double			rx;
	double			ry;
	double			rz;

	obj = data->selected_object;
	if (!obj || !obj->rotate_euler)
		return (0);
	get_rotation_angles(keycode, &rx, &ry, &rz);
	if (rx == 0.0 && ry == 0.0 && rz == 0.0)
		return (0);
	obj->rotate_euler((t_object *)obj, rx, ry, rz);
	return (1);
}

int	handle_scaling(t_data *data, int keycode)
{
	const t_object	*obj;
	double			k;

	obj = data->selected_object;
	if (obj && obj->scale_uniform
		&& (keycode == KEY_LEFT || keycode == KEY_RIGHT))
	{
		if (keycode == KEY_RIGHT)
			k = SCALE_STEP;
		else
			k = 1.0 / SCALE_STEP;
		obj->scale_uniform((t_object *)obj, k);
		return (1);
	}
	if (obj && obj->scale_height && (keycode == KEY_UP || keycode == KEY_DOWN))
	{
		if (keycode == KEY_UP)
			k = SCALE_STEP;
		else
			k = 1.0 / SCALE_STEP;
		obj->scale_height((t_object *)obj, k);
		return (1);
	}
	return (0);
}
