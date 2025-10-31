#ifndef CYLINDER_H
# define CYLINDER_H
# include "object.h"
# include "vector.h"
# include "color.h"
# include "material.h"

typedef struct s_cylinder
{
	t_object	base;
	t_vector3	center;
	t_vector3	orientation;
	double		diameter;
	double		height;
	t_color8	color;
}	t_cylinder;

int	cylinder_init(t_cylinder *cylinder, t_vector3 center, t_vector3 orientation,
			double diameter, double height, t_material material);

#endif
