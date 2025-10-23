#include <math.h>
#include "color.h"

static double	clamp01(double x)
{
	if (x < 0.0) return 0.0;
	if (x > 1.0) return 1.0;
	return x;
}

// IEC 61966-2-1: sRGB gamma
static double srgb_to_linear01(double colorSRGB) // cs in 0..1
{
    if (colorSRGB <= SRGB_K0)              
        return colorSRGB / SRGB_PHI;
    return pow((colorSRGB + SRGB_A) / SRGB_APLUS1, SRGB_GAMMA);
}

static double linear01_to_srgb(double colorLinear) // cl in 0..1
{
    if (colorLinear <= SRGB_K0_LINEAR)
        return (colorLinear * SRGB_PHI);
    return (SRGB_APLUS1 * pow(colorLinear, 1.0 / SRGB_GAMMA) - SRGB_A);
}

static uint8_t	to_u8(double x)
{
	int v;

	v = (int)floor(x * 255.0 + 0.5); /* round */
	if (v < 0) v = 0;
	if (v > 255) v = 255;
	return ((uint8_t)v);
}

t_color	color_make(double r, double g, double b)
{
	t_color c;

	c.r = r; c.g = g; c.b = b;
	return (c);
}

t_color8	color8_make(uint8_t r, uint8_t g, uint8_t b)
{
	t_color8 c;

	c.r = r; c.g = g; c.b = b;
	return (c);
}

t_color	color_from_rgb8(t_color8 color8)
{
	const double rs = (double)color8.r / 255.0;
	const double gs = (double)color8.g / 255.0;
	const double bs = (double)color8.b / 255.0;

	return (color_make(
		srgb_to_linear01(rs),
		srgb_to_linear01(gs),
		srgb_to_linear01(bs)));
}

t_color8	color_to_rgb8(t_color color)
{
	const double rs = linear01_to_srgb(clamp01(color.r));
	const double gs = linear01_to_srgb(clamp01(color.g));
	const double bs = linear01_to_srgb(clamp01(color.b));

	return (color8_make(to_u8(rs), to_u8(gs), to_u8(bs)));
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
