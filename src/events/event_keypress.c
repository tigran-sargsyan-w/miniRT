/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keypress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 00:14:19 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "constants.h"
#include "event_internal.h"
#include "mlx_utils.h"
#include <mlx.h>
#include <stdlib.h>

/**
 * @brief Handles Escape key behavior
 * If object selected: just deselect and rerender, else quit program
 * @param data - application state with scene and MLX
 * @return int - always 0 (MLX hook convention)
 */
int	handle_escape(t_data *data)
{
	if (data->selected_object)
	{
		data->selected_object = NULL;
		render_and_display(data);
		return (0);
	}
	free_scene(&data->scene);
	if (data->ray_dir_cache)
	{
		free(data->ray_dir_cache);
		data->ray_dir_cache = NULL;
	}
	free(data->objbuf);
	mlx_destroy_all(&data->mlx);
	exit(0);
	return (0);
}

/**
 * @brief Main keypress callback for MLX
 * Routes key events to object transform handlers
 * @param keycode - pressed key code
 * @param param - user param from MLX (cast to t_data *)
 * @return int - always 0 (MLX hook convention)
 */
int	on_keypress(int keycode, void *param)
{
	t_data	*data;
	int		changed;

	data = (t_data *)param;
	if (keycode == KEY_ESCAPE)
		return (handle_escape(data));
	if (!data->selected_object)
		return (0);
	changed = handle_translation(data, keycode);
	if (!changed)
		changed = handle_rotation(data, keycode);
	if (!changed)
		changed = handle_scaling(data, keycode);
	if (changed)
		render_and_display(data);
	return (0);
}
