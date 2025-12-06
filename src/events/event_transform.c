/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 16:32:11 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "constants.h"
#include "event_internal.h"
#include "vector.h"
#include <math.h>

static t_vector3	get_translation_delta(int keycode)
{
	t_vector3	d;

	d = vector3_zero();
	if (keycode == KeyA || keycode == KeyLeft)
		d.x = -MOVE_STEP;
	else if (keycode == KeyD || keycode == KeyRight)
		d.x = MOVE_STEP;
	else if (keycode == KeyQ)
		d.y = MOVE_STEP;
	else if (keycode == KeyE)
		d.y = -MOVE_STEP;
	else if (keycode == KeyW || keycode == KeyUp)
		d.z = MOVE_STEP;
	else if (keycode == KeyS || keycode == KeyDown)
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
	if (keycode == KeyI)
		*rx = step;
	else if (keycode == KeyK)
		*rx = -step;
	else if (keycode == KeyJ)
		*ry = step;
	else if (keycode == KeyL)
		*ry = -step;
	else if (keycode == KeyU)
		*rz = step;
	else if (keycode == KeyO)
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
		&& (keycode == KeyPageUp || keycode == KeyPageDown))
	{
		if (keycode == KeyPageUp)
			k = SCALE_STEP;
		else
			k = 1.0 / SCALE_STEP;
		obj->scale_uniform((t_object *)obj, k);
		return (1);
	}
	if (obj && obj->scale_height && (keycode == 93 || keycode == 91))
	{
		if (keycode == 93)
			k = SCALE_STEP;
		else
			k = 1.0 / SCALE_STEP;
		obj->scale_height((t_object *)obj, k);
		return (1);
	}
	return (0);
}
