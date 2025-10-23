#ifndef RAY_H
# define RAY_H
# include "vector.h"

typedef struct s_ray
{
	t_vector3	orig;
	t_vector3	dir;
}	t_ray;

t_ray		ray_make(t_vector3 orig, t_vector3 dir);
t_vector3	ray_at(const t_ray *ray, double distance);

#endif