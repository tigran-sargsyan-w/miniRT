#ifndef SPHERE_H
# define SPHERE_H
# include "object.h"

typedef struct s_sphere
{
	t_object	base;
	t_vector3	center;
	double		radius;
}	t_sphere;

int		sphere_init(t_sphere *sphere, t_vector3 center, double radius, t_material material);

#endif