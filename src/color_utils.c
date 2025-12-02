/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:25:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 18:25:40 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static double	clamp01(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

t_color	color_clamp01(t_color color)
{
	return (color_make(clamp01(color.r), clamp01(color.g), clamp01(color.b)));
}

t_color	color_lerp(t_color a, t_color b, double t)
{
	return (color_make(
			a.r * (1.0 - t) + b.r * t,
			a.g * (1.0 - t) + b.g * t,
			a.b * (1.0 - t) + b.b * t));
}
