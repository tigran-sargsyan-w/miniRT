/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:53:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 18:49:21 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

// sRGB color 0..255
typedef struct s_color8
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color8;

// sRGB converted to linear space
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

t_color		color_black(void);
t_color		color_white(void);

// sRGB conversion constants (IEC 61966-2-1)
# define SRGB_GAMMA          2.4
# define SRGB_A              0.055        /* "offset" */
# define SRGB_APLUS1         1.055        /* 1 + A */
# define SRGB_K0             0.04045      /* threshold (sRGB domain) */
# define SRGB_PHI            12.92        /* linear slope */
# define SRGB_K0_LINEAR      0.0031308    /* threshold (linear domain) 
                                            (SRGB_PHI * K0_LINEAR == K0) */

// Color constructors
t_color		color_make(double r, double g, double b);
t_color8	color8_make(uint8_t r, uint8_t g, uint8_t b);

// sRGB 0..255 to linear 0..1 and vice versa
t_color		color_from_rgb8(t_color8 color8);
t_color8	color_to_rgb8(t_color color);

// Basic operations (component-wise)
t_color		color_add(t_color a, t_color b);
t_color		color_multiply(t_color a, t_color b);
t_color		color_scale(t_color color, double k);
t_color		color_clamp01(t_color color);

// Utilities
t_color		color_lerp(t_color a, t_color b, double t);

#endif
