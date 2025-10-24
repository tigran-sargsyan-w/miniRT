#ifndef HIT_H
# define HIT_H
# include "vector.h"
# include "material.h"

typedef struct s_hit
{
	double				t;   // parameter t along the ray (like distance)
	t_vector3			hitPoint;   // intersection point
	t_vector3			normal;   // normal (unit vector)
	const t_material	*material; // material at the hit point
}	t_hit;

#endif