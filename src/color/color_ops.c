/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:28:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 19:02:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/**
 * @brief Creates linear color from RGB components
 * @param r - red component [0, 1]
 * @param g - green component [0, 1]
 * @param b - blue component [0, 1]
 * @return t_color - new color
 */
t_color	color_make(double r, double g, double b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

/**
 * @brief Creates 8-bit sRGB color from components
 * @param r - red component [0, 255]
 * @param g - green component [0, 255]
 * @param b - blue component [0, 255]
 * @return t_color8 - new 8-bit color
 */
t_color8	color8_make(uint8_t r, uint8_t g, uint8_t b)
{
	t_color8	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

/**
 * @brief Adds two colors component-wise
 * Used for combining light contributions
 * @param a - first color
 * @param b - second color
 * @return t_color - sum of colors
 */
t_color	color_add(t_color a, t_color b)
{
	return (color_make(a.r + b.r, a.g + b.g, a.b + b.b));
}

/**
 * @brief Multiplies two colors component-wise
 * Used for surface color * light color interaction
 * @param a - first color (e.g., surface)
 * @param b - second color (e.g., light)
 * @return t_color - product of colors
 */
t_color	color_multiply(t_color a, t_color b)
{
	return (color_make(a.r * b.r, a.g * b.g, a.b * b.b));
}

/**
 * @brief Scales color by a factor
 * Used for light intensity attenuation
 * @param color - color to scale
 * @param k - scale factor
 * @return t_color - scaled color
 */
t_color	color_scale(t_color color, double k)
{
	return (color_make(color.r * k, color.g * k, color.b * k));
}
