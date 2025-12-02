/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:28:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 18:28:43 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	color_make(double r, double g, double b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color8	color8_make(uint8_t r, uint8_t g, uint8_t b)
{
	t_color8	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	color_add(t_color a, t_color b)
{
	return (color_make(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color	color_multiply(t_color a, t_color b)
{
	return (color_make(a.r * b.r, a.g * b.g, a.b * b.b));
}

t_color	color_scale(t_color color, double k)
{
	return (color_make(color.r * k, color.g * k, color.b * k));
}
