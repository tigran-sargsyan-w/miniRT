#ifndef SPHERE_H
# define SPHERE_H
# include "object.h"
# include "vector.h"
# include "color.h"
# include "material.h"

typedef struct s_sphere
{
	t_object	base;
	t_vector3	center;
	t_color8	color;
	double		diameter;
}				t_sphere;

int				sphere_init(t_sphere *sphere, t_vector3 center, double diameter,
									t_material material);

#endif