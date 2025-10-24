#ifndef PLANE_H
# define PLANE_H
# include "object.h"

typedef struct s_plane
{
	t_object	base;
	t_vector3	point;
	t_vector3	normal;
}				t_plane;

int				plane_init(t_plane *plane, t_vector3 point, t_vector3 normal,
					t_material material);

#endif
