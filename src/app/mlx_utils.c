/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 00:20:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx_utils.h"
#include <mlx.h>
#include <stdlib.h>

/**
 * @brief Cleans up all MLX-related resources
 * Useful when exiting the program or on fatal error
 * @param mlx_data - MLX handles and image to destroy
 */
void	mlx_destroy_all(t_mlx_data *mlx_data)
{
	if (mlx_data->img.img_ptr)
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img.img_ptr);
	if (mlx_data->win_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data->mlx_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

/**
 * @brief Initializes MLX, window and image buffer
 * Call once at startup before rendering
 * @param mlx_data - output MLX state to initialize
 * @param name - window title string
 * @return int - 0 on success, 1 on failure
 */
int	mlx_init_system(t_mlx_data *mlx_data, char *name)
{
	ft_bzero(mlx_data, sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data->mlx_ptr == NULL)
		return (1);
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIDTH, HEIGHT, name);
	if (mlx_data->win_ptr == NULL)
		return (1);
	mlx_data->img.img_ptr = mlx_new_image(mlx_data->mlx_ptr, WIDTH, HEIGHT);
	if (mlx_data->img.img_ptr == NULL)
		return (1);
	mlx_data->img.pixels_ptr = mlx_get_data_addr(mlx_data->img.img_ptr,
			&mlx_data->img.bits_per_pixel, &mlx_data->img.line_length,
			&mlx_data->img.endian);
	return (0);
}

/**
 * @brief Writes a pixel color into MLX image buffer
 * Very useful in render loop for drawing each pixel
 * @param image_data - target image buffer
 * @param x - x pixel coordinate
 * @param y - y pixel coordinate
 * @param color - packed integer color value
 */
void	my_mlx_pixel_put(t_img_data *image_data, int x, int y, int color)
{
	char	*dst;

	dst = image_data->pixels_ptr + (y * image_data->line_length + x
			* (image_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
