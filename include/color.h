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

# define COLOR_BLACK   ((t_color){0.0, 0.0, 0.0})
# define COLOR_WHITE   ((t_color){1.0, 1.0, 1.0})

// Color constructors
t_color		color_make(double r, double g, double b);
t_color8	color8_make(uint8_t r, uint8_t g, uint8_t b);

// sRGB 0..255 to linear 0..1 and vice versa
t_color		color_from_rgb8(t_color8 color8);
t_color8	color_to_rgb8(t_color color);

// Basic operations (component-wise)
t_color		color_add(t_color a, t_color b);
t_color		color_multiply(t_color a, t_color b);     // a ⊙ b (albedo * light)
t_color		color_scale(t_color color, double k);     // c * k
t_color		color_clamp01(t_color color);

// Utilities
t_color		color_lerp(t_color a, t_color b, double t);

#endif
