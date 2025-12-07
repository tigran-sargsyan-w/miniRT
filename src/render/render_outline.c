/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_outline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:12:17 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:33:02 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "constants.h"

/**
 * @brief Checks whether pixel has left/right neighbor from different object
 * @param data - application state with objbuf and selected_object
 * @param x - pixel X coordinate
 * @param y - pixel Y coordinate
 * @return int - 1 if edge on left/right, 0 otherwise
 */
static int	is_edge_left_right(t_data *data, int x, int y)
{
	if (x <= 0)
		return (1);
	if (data->objbuf[y * WIDTH + (x - 1)] != data->selected_object)
		return (1);
	if (x >= WIDTH - 1)
		return (1);
	if (data->objbuf[y * WIDTH + (x + 1)] != data->selected_object)
		return (1);
	return (0);
}

/**
 * @brief Checks whether pixel has top/bottom neighbor from different object
 * @param data - application state with objbuf and selected_object
 * @param x - pixel X coordinate
 * @param y - pixel Y coordinate
 * @return int - 1 if edge on top/bottom, 0 otherwise
 */
static int	is_edge_top_bottom(t_data *data, int x, int y)
{
	if (y <= 0)
		return (1);
	if (data->objbuf[(y - 1) * WIDTH + x] != data->selected_object)
		return (1);
	if (y >= HEIGHT - 1)
		return (1);
	if (data->objbuf[(y + 1) * WIDTH + x] != data->selected_object)
		return (1);
	return (0);
}

/**
 * @brief Combined edge test horizontally and vertically
 * @param data - application state
 * @param x - pixel X coordinate
 * @param y - pixel Y coordinate
 * @return int - 1 if any neighboring pixel differs
 */
static int	is_edge(t_data *data, int x, int y)
{
	if (is_edge_left_right(data, x, y))
		return (1);
	if (is_edge_top_bottom(data, x, y))
		return (1);
	return (0);
}

/**
 * @brief Draws outline for a single scanline (row)
 * @param data - application state with objbuf and MLX image
 * @param y - scanline index
 */
static void	draw_outline_row(t_data *data, int y)
{
	int				x;
	const t_object	*o;

	x = 0;
	while (x < WIDTH)
	{
		o = data->objbuf[y * WIDTH + x];
		if (o == data->selected_object && is_edge(data, x, y))
			my_mlx_pixel_put(&data->mlx.img, x, y, OUTLINE_COLOR);
		x++;
	}
}

/**
 * @brief Draws object outline over rendered image for selected object
 * Iterates all rows and marks edge pixels with outline color
 * @param data - application state
 */
void	draw_outline(t_data *data)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		draw_outline_row(data, y);
		y++;
	}
}
