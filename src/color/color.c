/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:39:41 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 19:04:09 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"

/**
 * @brief Converts sRGB component to linear space
 * @param color_srgb - sRGB value [0, 1]
 * @return double - linear value [0, 1]
 */
static double	srgb_to_linear01(double color_srgb)
{
	if (color_srgb <= SRGB_K0)
		return (color_srgb / SRGB_PHI);
	return (pow((color_srgb + SRGB_A) / SRGB_APLUS1, SRGB_GAMMA));
}

/**
 * @brief Converts linear component to sRGB space
 * @param color_linear - linear value [0, 1]
 * @return double - sRGB value [0, 1]
 */
static double	linear01_to_srgb(double color_linear)
{
	if (color_linear <= SRGB_K0_LINEAR)
		return (color_linear * SRGB_PHI);
	return (SRGB_APLUS1 * pow(color_linear, 1.0 / SRGB_GAMMA) - SRGB_A);
}

/**
 * @brief Converts [0,1] float to [0,255] uint8 with rounding
 * @param x - value in [0, 1] range
 * @return uint8_t - clamped integer [0, 255]
 */
static uint8_t	to_u8(double x)
{
	int	v;

	v = (int)floor(x * 255.0 + 0.5);
	if (v < 0)
		v = 0;
	if (v > 255)
		v = 255;
	return ((uint8_t)v);
}

/**
 * @brief Converts 8-bit sRGB color to linear floating-point
 * Use when loading colors from file/parsing
 * @param color8 - sRGB color with 8-bit components
 * @return t_color - linear color for calculations
 */
t_color	color_from_rgb8(t_color8 color8)
{
	double	rs;
	double	gs;
	double	bs;

	rs = (double)color8.r / 255.0;
	gs = (double)color8.g / 255.0;
	bs = (double)color8.b / 255.0;
	return (color_make(
			srgb_to_linear01(rs),
			srgb_to_linear01(gs),
			srgb_to_linear01(bs)));
}

/**
 * @brief Converts linear color to 8-bit sRGB for display
 * Use when outputting final pixel color
 * @param color - linear color after lighting calculations
 * @return t_color8 - sRGB color ready for display
 */
t_color8	color_to_rgb8(t_color color)
{
	t_color	clamped;
	double	rs;
	double	gs;
	double	bs;

	clamped = color_clamp01(color);
	rs = linear01_to_srgb(clamped.r);
	gs = linear01_to_srgb(clamped.g);
	bs = linear01_to_srgb(clamped.b);
	return (color8_make(to_u8(rs), to_u8(gs), to_u8(bs)));
}
