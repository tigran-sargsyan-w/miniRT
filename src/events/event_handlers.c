/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 22:48:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "event_internal.h"
#include "mlx_utils.h"
#include <mlx.h>
#include <stdlib.h>

void	render_and_display(t_data *data)
{
	if (render_scene(data) == 0)
	{
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
			data->mlx.img.img_ptr, 0, 0);
	}
}

static int	on_destroy(void *param)
{
	t_data	*data;

	data = (t_data *)param;
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

void	install_event_handlers(t_data *data)
{
	if (!data || !data->mlx.win_ptr)
		return ;
	mlx_key_hook(data->mlx.win_ptr, &on_keypress, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, &on_destroy, data);
	mlx_mouse_hook(data->mlx.win_ptr, &on_mouse, data);
}
