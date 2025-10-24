#ifndef LIGHT_H
# define LIGHT_H
# include "vector.h"
# include "color.h"

typedef struct s_light
{
	t_vector3		position;
	t_color			color;     // linear 0..1
	double			intensity; // 0..∞
}	t_light;

t_light	light_point_make(t_vector3 position, t_color8 color, double intensity);
#endif