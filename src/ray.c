#include "ray.h"

t_ray	ray_make(t_vector3 orig, t_vector3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}
    
t_vector3	ray_at(const t_ray *ray, double distance)
{
    return (vector3_add(ray->orig, vector3_scale(ray->dir, distance)));
}