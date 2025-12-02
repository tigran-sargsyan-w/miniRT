/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:25:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 19:03:19 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/**
 * @brief Clamps value to [0, 1] range
 * @param x - input value
 * @return double - clamped value
 */
static double	clamp01(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

/**
 * @brief Clamps all color components to [0, 1]
 * Use before converting to RGB8 for display
 * @param color - input color
 * @return t_color - clamped color
 */
t_color	color_clamp01(t_color color)
{
	return (color_make(clamp01(color.r), clamp01(color.g), clamp01(color.b)));
}

/**
 * @brief Linear interpolation between two colors
 * Result = a*(1-t) + b*t
 * @param a - start color (t=0)
 * @param b - end color (t=1)
 * @param t - interpolation factor [0, 1]
 * @return t_color - interpolated color
 */
t_color	color_lerp(t_color a, t_color b, double t)
{
	return (color_make(
			a.r * (1.0 - t) + b.r * t,
			a.g * (1.0 - t) + b.g * t,
			a.b * (1.0 - t) + b.b * t));
}

/**
 * @brief Returns black color (0, 0, 0)
 * @return t_color - black
 */
t_color	color_black(void)
{
	return (color_make(0.0, 0.0, 0.0));
}

/**
 * @brief Returns white color (1, 1, 1)
 * @return t_color - white
 */
t_color	color_white(void)
{
	return (color_make(1.0, 1.0, 1.0));
}
