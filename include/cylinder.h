#ifndef CYLINDER_H
# define CYLINDER_H
# include "object.h"

typedef struct s_cylinder
{
	t_object	base;
	t_vector3	center; //center of the cylinder
	t_vector3	axis; //unit vector along the axis (direction +Z "local")
	double		radius;
	double		half_height;
}	t_cylinder;

int	cylinder_init(t_cylinder *cylinder, t_vector3 center, t_vector3 axis,
			double radius, double height, t_material material);

#endif
